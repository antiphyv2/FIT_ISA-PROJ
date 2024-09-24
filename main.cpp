#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

int main(int argc, char** argv){
    
    DEBUG_PRINT("Starting isa project..." << std::endl);

    std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();

    try {
        sniffer->getParser()->parseArgs(argc, argv);

        DEBUG_PRINT("Interface: " << sniffer->getParser()->getInterface() << std::endl);
        DEBUG_PRINT("Sort by packets: " << sniffer->getParser()->getSortPackets() << std::endl);
        DEBUG_PRINT("Sort by bytes: " << sniffer->getParser()->getSortBytes() << std::endl);
        DEBUG_PRINT("List interfaces: " << sniffer->getParser()->getPrintInterfaces() << std::endl);

        sniffer->sniffThePackets();
    } catch (const argParserException& e) {
        std::cerr << e.what() << std::endl;
        //If return code was not from -h switch, exit the program as a failure
        if(e.getRetCode() != PRINT_HELP){
            exit(EXIT_FAILURE);
        }
    } catch (const packetSnifferException& e){
        std::cerr << e.what() << std::endl;
        if(e.getRetCode() != SNIFFER_OK){
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

