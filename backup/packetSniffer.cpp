#include "packetSniffer.hpp"

packetSniffer::packetSniffer(){}

packetSniffer::~packetSniffer(){}

parsedArgs packetSniffer::getCommandLineArgs(){
    return this->cliArgs;
}

void packetSniffer::setCommandLineArgs(parsedArgs cliArgs){
    this->cliArgs = cliArgs;
}