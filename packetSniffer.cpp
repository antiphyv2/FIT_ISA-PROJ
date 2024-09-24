#include "packetSniffer.hpp"

packetSniffer::packetSniffer(){}

packetSniffer::~packetSniffer(){}

cliParser* packetSniffer::getParser(){
    return &this->parser;
}