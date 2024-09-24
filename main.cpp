#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

int main(int argc, char** argv){
    
    DEBUG_PRINT("Starting isa project..." << std::endl);

    std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();

    try {

        DEBUG_PRINT("Parsing arguments..." << std::endl);

        sniffer->getParser()->parseArgs(argc, argv);

        DEBUG_PRINT("Interface: " << sniffer->getParser()->getInterface() << std::endl);
        DEBUG_PRINT("Sort by packets: " << sniffer->getParser()->getSortPackets() << std::endl);
        DEBUG_PRINT("Sort by bytes: " << sniffer->getParser()->getSortBytes() << std::endl);
        DEBUG_PRINT("List interfaces: " << sniffer->getParser()->getPrintInterfaces() << std::endl);

        const auto& parser = sniffer->getParser();
        if(parser->getInterfacesFlag()){
            sniffer->listInterfaces();
            return(EXIT_SUCCESS);
        } else if (parser->getHelpFlag()){
            parser->printHelp();
            return(EXIT_SUCCESS);
        }

        sniffer->sniffThePackets();
    } catch (const argParserException& e) {
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);

    } catch (const packetSnifferException& e){
        std::cerr << e.what() << std::endl;
        if(e.getRetCode() != SNIFFER_OK){
            exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}

