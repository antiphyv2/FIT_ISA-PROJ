#include "packetSniffer.hpp"
#include "exceptions.hpp"

packetSniffer::packetSniffer(){}

packetSniffer::~packetSniffer(){}

cliParser* packetSniffer::getParser(){
    return &this->parser;
}

void packetSniffer::sniffThePackets(){

    DEBUG_PRINT("Starting the packet sniffer..." << std::endl);

    throw packetSnifferException(SNIFFER_OK, "Sniffer ended correctly.");
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