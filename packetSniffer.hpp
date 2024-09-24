#ifndef PACKET_SNIFFER_HPP
#define PACKET_SNIFFER_HPP

#include "cliparser.hpp"

class packetSniffer {

private:
    cliParser parser;
public:
    
    packetSniffer();
    ~packetSniffer();
    cliParser* getParser();
    void sniffThePackets();
    static void listInterfaces();
};
#endif