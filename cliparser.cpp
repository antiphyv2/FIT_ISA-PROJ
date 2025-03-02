/**
 * @file cliparser.cpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Implementation of the functions for parsing command line arguments
 */

#include "cliparser.hpp"
#include "main.hpp"
#include "exceptions.hpp"
#include "packetSniffer.hpp"

void cliParser::printHelp(){
    std::cout << "Usage: ./isa-top -i interface -s -p|b" << std::endl;
}

void cliParser::parseArgs(int argc, char** argv){
    int option;
    int interval = 1;
    while((option = getopt(argc, argv, "i:s:t:hl")) != -1){
        switch(option){
            case 'i':
                this->interface = optarg;
                break;
            case 'h':
                //Print help message
                this->printHelp();
                throw argParserException(PRINT, "");
            case 's':
                //Check if the argument is correct
                if(strlen(optarg) != 1 || (optarg[0] != 'b' && optarg[0] != 'p')){
                    throw argParserException(ERROR, "ERR: -s parameter can only have b|p argument, see -h for usage.");
                }

                //Argumente is set twice
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
                //List all interfaces
                packetSniffer::listInterfaces();
                throw argParserException(LIST_INTERFACE, "");
            case 't':
                char* pointer;
                interval = (int) strtol(optarg, &pointer, 10);
                if(*pointer != 0 || interval <= 0){
                    throw argParserException(ERROR, "ERR: Time interval must be positive a number.");
                }
                this->refreshInterval = interval;
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
