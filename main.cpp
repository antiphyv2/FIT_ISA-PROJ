#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

//Global variable to be able to close it after signal is caught
std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();

void gracefulExit(int sig){
    DEBUG_PRINT("CTRL+C caught, exiting sniffer..." << std::endl);
    pcap_close(sniffer->getSniffer());
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    
    DEBUG_PRINT("Starting isa project..." << std::endl);

    signal(SIGINT, gracefulExit);  

    try {

        DEBUG_PRINT("Parsing arguments..." << std::endl);

        sniffer->getParser()->parseArgs(argc, argv);

        DEBUG_PRINT("Interface: " << sniffer->getParser()->getInterface() << std::endl);
        DEBUG_PRINT("Sort by packets: " << sniffer->getParser()->getSortPackets() << std::endl);
        DEBUG_PRINT("Sort by bytes: " << sniffer->getParser()->getSortBytes() << std::endl);

        sniffer->sniffThePackets();
    } catch (const argParserException& e) {
        if(e.getRetCode() != PRINT){
            std::cerr << e.what() << std::endl;
            return(EXIT_FAILURE);
        }
    } catch (const packetSnifferException& e){
        std::cerr << e.what() << std::endl;
        if(e.getRetCode() != SNIFFER_OK){
            return(EXIT_FAILURE);
        }
    }

    DEBUG_PRINT("Ending isa project..." << std::endl);

    return EXIT_SUCCESS;
}

