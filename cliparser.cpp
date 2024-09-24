#include "cliparser.hpp"
#include "main.hpp"
#include "exceptions.hpp"
#include "packetSniffer.hpp"

void cliParser::printHelp(){
    std::cout << "Usage: ./isa-top -i interface -s -p|b" << std::endl;
}

void cliParser::parseArgs(int argc, char** argv){
    DEBUG_PRINT("Arg number: " << argc << std::endl);

    int option;
    while((option = getopt(argc, argv, "i:s:hl")) != -1){
        switch(option){
            case 'i':
                this->interface = optarg;
                break;
            case 'h':
                this->printHelp();
                throw argParserException(PRINT, "");
            case 's':
                if(strlen(optarg) != 1 || (optarg[0] != 'b' && optarg[0] != 'p')){
                    throw argParserException(ERROR, "ERR: -s parameter can only have b|p argument, see -h for usage.");
                }

                if(this->sortBytes || this->sortPackets){
                    throw argParserException(ERROR, "ERR: You can sort only by 1 parameter at once.");
                }

                if(optarg[0] == 'b'){
                    this->sortBytes = true;
                } else {
                    this->sortPackets = true;
                }
                break;
            case 'l':
                packetSniffer::listInterfaces();
                throw argParserException(PRINT, "");
            default:
                throw argParserException(DEFAULT, "Try ./isa-top -h for help.");
        }
    }
}

std::string cliParser::getInterface(){
    return this->interface;
}

bool cliParser::getSortPackets(){
    return this->sortPackets;
}

bool cliParser::getSortBytes(){
    return this->sortBytes;
}

void cliParser::setInterface(std::string interface){
    this->interface = interface;
}

void cliParser::setSortPackets(bool sortPackets){
    this->sortPackets = sortPackets;
}

void cliParser::setSortBytes(bool sortBytes){
    this->sortBytes = sortBytes;
}
