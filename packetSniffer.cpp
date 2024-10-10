#include "packetSniffer.hpp"
#include "exceptions.hpp"

packetSniffer::packetSniffer(){
    this->sniffer = NULL;
    this->errbuf[0] = '\0';
}

packetSniffer::~packetSniffer(){}

cliParser* packetSniffer::getParser(){
    return &this->parser;
}

pcap_t* packetSniffer::getSniffer(){
    return this->sniffer;
}

void packetSniffer::runSniffer(int argc, char** argv, std::promise<int> promise){

    int exit_value = EXIT_SUCCESS;

    try {
        this->sniffThePackets();
    } catch (const packetSnifferException& e){
        std::cerr << e.what() << std::endl;
        if(e.getRetCode() != SNIFFER_OK){
            exit_value = EXIT_FAILURE;
        }
    }
    promise.set_value(exit_value);
}

//All functions needed to create the sniffer are taken from my IPK2 projecct and are based on an example from
//https://vichargrave.github.io/programming/develop-a-packet-sniffer-with-libpcap/#build-and-run-the-sniffer

void packetSniffer::sniffThePackets(){

    DEBUG_PRINT("Starting the packet sniffer..." << std::endl);

    
    sniffer = pcap_open_live(this->getParser()->getInterface().c_str(), BUFSIZ, 1, 1000, errbuf);
    if(!sniffer){
        std::cerr << "ERROR: [PCAP_OPEN_LIVE] Interface named ";
        throw packetSnifferException(SNIFFER_ERROR, errbuf);
    }

    // int retCode = pcap_loop(sniffer, 0, packetParser, NULL);
    // if(retCode == -1){
    //     std::cerr << "ERROR: [PCAP_LOOP]";
    //     throw packetSnifferException(SNIFFER_ERROR, pcap_geterr(sniffer));
    // }
    while(snifferFlag.load()){
        pcap_pkthdr header;
        const u_char* packet = pcap_next(this->sniffer, &header);
        if(packet == NULL){
            std::cerr << "ERROR: [PCAP_NEXT]";
            throw packetSnifferException(SNIFFER_ERROR, pcap_geterr(sniffer));
        }
        packetParser(NULL, &header, packet);
    }


    pcap_close(sniffer);
    throw packetSnifferException(SNIFFER_OK, "Sniffer ended correctly.");
}

void packetSniffer::packetParser(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet){

    DEBUG_PRINT("Parsing packet..." << std::endl);

    //Print frame length
    printf("frame length: %u\n", pkthdr->len);

    //Find out if type is IPV4, IPV6
    uint16_t ethernet_type = ntohs(((struct ether_header*) packet)->ether_type);

    //Now we can skip the datalink ethernet header and get to the ip header
    packet += 14;

    switch (ethernet_type){

    case ETHERTYPE_IP: {
        //Get the ip header to determine protocol
        struct ip* ip_header = (struct ip*) packet;
        std::cout << "src IP: " << inet_ntoa(ip_header->ip_src) << std::endl;
        std::cout << "dst IP: " << inet_ntoa(ip_header->ip_dst) << std::endl;;
        if (ip_header->ip_p == IPPROTO_TCP) {
            printf("packet type: ipv4 TCP\n");
        } else if (ip_header->ip_p == IPPROTO_UDP) {
            printf("packet type: ipv4 UDP\n");
        } else if(ip_header->ip_p == IPPROTO_ICMP) {
            printf("packet type: ipv4 ICMP\n");
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

        std::cout << "src IPv6: " << src_ipv6 << std::endl;
        std::cout << "dst IP: " << dst_ipv6 << std::endl;;

        uint8_t next_header = ipv6_header->ip6_ctlun.ip6_un1.ip6_un1_nxt;
        if(next_header == IPPROTO_TCP){
            printf("packet type: ipv6 TCP\n");
        } else if(next_header == IPPROTO_UDP){
            printf("packet type: ipv6 UDP\n");
        } else if(next_header == IPPROTO_ICMPV6){
            printf("packet type: ipv6 ICMPv6\n");
        }
        break;
    }

    default:
        break;
    }
    DEBUG_PRINT("Packet parsed..." << std::endl);

}

void packetSniffer::listInterfaces(){

    DEBUG_PRINT("Listing available interfaces..." << std::endl);

    pcap_if_t *networkDevices;
    char errbuf[PCAP_ERRBUF_SIZE];

    //Get a list of all devices
    if (pcap_findalldevs(&networkDevices, errbuf) == -1) {
        std::cerr << "ERROR: [PCAP_FINDALL]";
        throw packetSnifferException(INTERFACE_ERROR, errbuf);
    }

    std::cout << "List of available network interfaces:" << std::endl;

    pcap_if_t *dev = networkDevices;
    int int_count = 1;
    //Iterate through devices and print description if exists
    while(dev){
        if(dev->description){
            std::cout << int_count << ". interface: " << dev->name << ", Description: " << dev->description << std::endl;
        } else {
            std::cout << int_count << ". interface: " << dev->name << ", No description available" << std::endl;
        }
        int_count++;
        dev = dev->next;
    }

    DEBUG_PRINT("All interfaces listed..." << std::endl);

    pcap_freealldevs(networkDevices);

}