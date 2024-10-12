#include "cliparser.hpp"
#include "main.hpp"
#include "exceptions.hpp"
#include "packetSniffer.hpp"

void cliParser::printHelp(){
    std::cout << "Usage: ./isa-top -i interface -s -p|b" << std::endl;
}

void cliParser::parseArgs(int argc, char** argv){
    int option;
    while((option = getopt(argc, argv, "i:s:t:hl")) != -1){
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

                if(this->sortType == BYTE || this->sortType == PACKET){
                    throw argParserException(ERROR, "ERR: You can sort only by 1 parameter at once.");
                }

                if(optarg[0] == 'b'){
                    this->sortType = BYTE;
                } else {
                    this->sortType = PACKET;
                }
                break;
            case 'l':
                packetSniffer::listInterfaces();
                throw argParserException(LIST_INTERFACE, "");
            case 't':
                char* pointer;
                this->refreshInterval = (int) strtol(optarg, &pointer, 10);
                if(*pointer != 0){
                    throw argParserException(ERROR, "ERR: Time interval must be a number.");
                }
                break;
            default:
                throw argParserException(DEFAULT, "Try ./isa-top -h for help.");
        }
    }

}

std::string cliParser::getInterface(){
    return this->interface;
}

int cliParser::getRefreshInterval(){
    return this->refreshInterval;
}

sortBy cliParser::getSortType(){
    return this->sortType;
}
