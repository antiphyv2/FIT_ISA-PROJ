#include "packetSniffer.hpp"
#include "exceptions.hpp"

packetSniffer::packetSniffer(){}

packetSniffer::~packetSniffer(){}

cliParser* packetSniffer::getParser(){
    return &this->parser;
}

void packetSniffer::sniffThePackets(){

    DEBUG_PRINT("Starting the packet sniffer" << std::endl);

    throw packetSnifferException(SNIFFER_OK, "Sniffer ended correctly.");
}