#include "cliparser.hpp"
#include "main.hpp"
#include "exceptions.hpp"

void cliParser::parseArgs(int argc, char** argv, parsedArgs& argStruct){
    DEBUG_PRINT("Arg number: " << argc << std::endl);

    int option;
    while((option = getopt(argc, argv, "i:s:hl")) != -1){
        switch(option){
            case 'i':
                argStruct.interface = optarg;
                break;
            case 'h':
                throw argParserException(PRINT_HELP, "Usage: ./isa-top -i interface -s -p|b");
                break;
            case 's':
                if(strlen(optarg) != 1 || (optarg[0] != 'b' && optarg[0] != 'p')){
                    throw argParserException(ERROR, "ERR: -s parameter can only have b|p argument, see -h for usage.");
                }

                if(argStruct.sortBytes || argStruct.sortPackets){
                    throw argParserException(ERROR, "ERR: You can sort only by 1 parameter at once.");
                }

                if(optarg[0] == 'b'){
                    argStruct.sortBytes = true;
                } else {
                    argStruct.sortPackets = true;
                }
                break;
            case 'l':
                argStruct.printInterfaces = true;
                break;
            default:
                throw argParserException(DEFAULT,"See -h for usage.");
        }
    }
}