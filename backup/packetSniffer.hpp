#ifndef PACKET_SNIFFER_HPP
#define PACKET_SNIFFER_HPP

#include "cliparser.hpp"

class packetSniffer {

private:
    parsedArgs cliArgs;
public:
    
    packetSniffer();
    ~packetSniffer();
    parsedArgs getCommandLineArgs();
    void setCommandLineArgs(parsedArgs args);
};
#endif