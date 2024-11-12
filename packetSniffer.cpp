#include "packetSniffer.hpp"
#include "exceptions.hpp"

packetSniffer::packetSniffer(){
    this->sniffer = NULL;
}

packetSniffer::~packetSniffer(){}

cliParser* packetSniffer::getParser(){
    return &this->parser;
}

pcap_t* packetSniffer::getSniffer(){
    return this->sniffer;
}

void packetSniffer::runSniffer(std::promise<int> promise, connectionManager* manager, std::unique_ptr<packetDisplay>& display){
    int exit_value = EXIT_SUCCESS;

    //Sniff the packets and catch errors as exceptions
    try {
        this->sniffThePackets(manager);
    } catch (const packetSnifferException& e){
        display->clearScreen();
        std::cerr << e.what() << std::endl;

        if(e.getRetCode() != SNIFFER_OK){
            exit_value = EXIT_FAILURE;
        }
        
    }

    //Set the promise value for the main thread later on
    promise.set_value(exit_value);
}

//All functions needed to create the sniffer are taken from my IPK2 projecct and are based on an example from
//https://vichargrave.github.io/programming/develop-a-packet-sniffer-with-libpcap/#build-and-run-the-sniffer

void packetSniffer::sniffThePackets(connectionManager* manager){

    char errbuf[PCAP_ERRBUF_SIZE];

    //Open the sniffer
    sniffer = pcap_open_live(this->getParser()->getInterface().c_str(), BUFSIZ, 1, 1000, errbuf);

    //Sniffer could not be opened
    if(!sniffer){
        snifferFlag.store(false);
        throw packetSnifferException(SNIFFER_ERROR, "ERROR: [PCAP_OPEN_LIVE] Interface named " + std::string(errbuf));
    }

    //Parse the packets in a loop
    if (pcap_loop(sniffer, 0, packetParser, reinterpret_cast<u_char*>(manager)) != 0) {
        if(snifferFlag.load() != false){
            throw packetSnifferException(SNIFFER_ERROR, "ERROR: [PCAP_LOOP] " + std::string(pcap_geterr(sniffer)));
        }
        
    }

    //Close the sniffer after breaking the loop
    pcap_close(sniffer);
}

void packetSniffer::packetParser(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet){

    connectionManager* manager = reinterpret_cast<connectionManager*>(user);
    connectionInfo capturedPacket = {};

    //Get packet length
    int packetLength = pkthdr->len;

    //Find out if type is IPv4, IPv6
    uint16_t ethernet_type = ntohs(((struct ether_header*) packet)->ether_type);

    //Now we can skip the datalink ethernet header and get to the IP header
    packet += 14;

    switch (ethernet_type){

    case ETHERTYPE_IP: {
        //Get the ip header to determine protocol
        struct ip* ip_header = (struct ip*) packet;
        capturedPacket.dstIP = std::string(inet_ntoa(ip_header->ip_dst));
        capturedPacket.srcIP = std::string(inet_ntoa(ip_header->ip_src));

        if (ip_header->ip_p == IPPROTO_TCP) {
            capturedPacket.protocol.append("tcp");

            //Multiply by 4 to convert it to bytes (length in 32bit words)
            struct tcphdr* tcp_header = (struct tcphdr *) ((unsigned char*)ip_header + ip_header->ip_hl * 4);

            //Set the source and destination ports 
            capturedPacket.srcPort = ntohs(tcp_header->th_sport);
            capturedPacket.dstPort = ntohs(tcp_header->th_dport);
        } else if (ip_header->ip_p == IPPROTO_UDP) {
            capturedPacket.protocol.append("udp");

            //Multiply by 4 to convert it to bytes (length in 32bit words)
            struct udphdr *udp_header = (struct udphdr *) ((unsigned char*)ip_header + ip_header->ip_hl * 4); 

            //Set the source and destination ports
            capturedPacket.srcPort = ntohs(udp_header->uh_sport);
            capturedPacket.dstPort = ntohs(udp_header->uh_dport);
        } else if(ip_header->ip_p == IPPROTO_ICMP) {
            capturedPacket.protocol.append("icmp");
        }
        break;
    }

    case ETHERTYPE_IPV6: {
        struct ip6_hdr* ipv6_header = (struct ip6_hdr*) packet;

        char src_ipv6[INET6_ADDRSTRLEN];
        char dst_ipv6[INET6_ADDRSTRLEN];

        //Use inet_ntop since inet_ntoa is only used for ipv4 addresses, it should also be fine with RFC 5952 when reading this site: https://pubs.opengroup.org/onlinepubs/009604499/functions/inet_ntop.html
        inet_ntop(AF_INET6, &ipv6_header->ip6_src, src_ipv6, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &ipv6_header->ip6_dst, dst_ipv6, INET6_ADDRSTRLEN);

        capturedPacket.srcIP = src_ipv6;
        capturedPacket.dstIP = dst_ipv6;

        //IPv6 header length is always 40 bytes
        int ipv6_header_length = 40;

        uint8_t next_header = ipv6_header->ip6_ctlun.ip6_un1.ip6_un1_nxt;
        if(next_header == IPPROTO_TCP){
            capturedPacket.protocol.append("tcp");
            capturedPacket.srcPort = ntohs(((struct tcphdr*) (packet + ipv6_header_length))->th_sport);
            capturedPacket.dstPort = ntohs(((struct tcphdr*) (packet + ipv6_header_length))->th_dport);
        } else if(next_header == IPPROTO_UDP){
            capturedPacket.protocol.append("udp");
            capturedPacket.srcPort = ntohs(((struct udphdr*) (packet + ipv6_header_length))->uh_sport);
            capturedPacket.dstPort = ntohs(((struct udphdr*) (packet + ipv6_header_length))->uh_dport);
        } else if(next_header == IPPROTO_ICMPV6){
            capturedPacket.protocol.append("icmp");
        }
        break;
    }

    default:
        return;
    }

    manager->addConnection(capturedPacket, packetLength);
}

void packetSniffer::listInterfaces(){

    pcap_if_t *networkDevices;
    char errbuf[PCAP_ERRBUF_SIZE];

    //Get a list of all devices
    if (pcap_findalldevs(&networkDevices, errbuf) == -1) {
        std::cerr << "ERROR: [PCAP_FINDALL]";
        throw packetSnifferException(INTERFACE_ERROR, errbuf);
    }

    std::cout << "List of available network interfaces:" << std::endl;


    pcap_if_t *dev = networkDevices;
    int interfaceNumber = 1;

    //Iterate through devices and print description if exists
    while(dev){
        if(dev->description){
            std::cout << interfaceNumber << ". interface: " << dev->name << ", Description: " << dev->description << std::endl;
        } else {
            std::cout << interfaceNumber << ". interface: " << dev->name << ", No description available" << std::endl;
        }
        interfaceNumber++;
        dev = dev->next;
    }

    //Free the allocated memory
    pcap_freealldevs(networkDevices);

}