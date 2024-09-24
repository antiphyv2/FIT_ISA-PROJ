#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

int main(int argc, char** argv){
    
    DEBUG_PRINT("Starting isa project..." << std::endl);

    std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();

    try {
        sniffer->getParser()->parseArgs(argc, argv);
    } catch (const argParserException& e) {
        std::cerr << e.what() << std::endl;
        //If return code was not from -h switch, exit the program as a failure
        if(e.getRetCode() != PRINT_HELP){
            exit(EXIT_FAILURE);
        }
    }

    DEBUG_PRINT("Interface: " << sniffer->getParser()->getInterface() << std::endl);
    DEBUG_PRINT("Sort by packets: " << sniffer->getParser()->getSortPackets() << std::endl);
    DEBUG_PRINT("Sort by bytes: " << sniffer->getParser()->getSortBytes() << std::endl);
    DEBUG_PRINT("List interfaces: " << sniffer->getParser()->getPrintInterfaces() << std::endl);

    //std::cout << sniffer->getParser()->getInterface() << std::endl;

    return EXIT_SUCCESS;
}

