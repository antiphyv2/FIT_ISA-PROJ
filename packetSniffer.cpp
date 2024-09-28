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

//All functions needed to create the sniffer are taken from my IPK2 projecct and are based on an example from
//https://vichargrave.github.io/programming/develop-a-packet-sniffer-with-libpcap/#build-and-run-the-sniffer

void packetSniffer::sniffThePackets(){

    DEBUG_PRINT("Starting the packet sniffer..." << std::endl);

    
    sniffer = pcap_open_live(this->getParser()->getInterface().c_str(), BUFSIZ, 1, 1000, errbuf);
    if(!sniffer){
        std::cerr << "ERROR: [PCAP_OPEN_LIVE] Interface named ";
        throw packetSnifferException(SNIFFER_ERROR, errbuf);
    }

    int retCode = pcap_loop(sniffer, -1, packetParser, NULL);
    if(retCode == -1){
        std::cerr << "ERROR: [PCAP_LOOP]";
        throw packetSnifferException(SNIFFER_ERROR, pcap_geterr(sniffer));
    }

    pcap_close(sniffer);
    throw packetSnifferException(SNIFFER_OK, "Sniffer ended correctly.");
}

void packetSniffer::packetParser(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet){

    DEBUG_PRINT("Parsing packet..." << std::endl);

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