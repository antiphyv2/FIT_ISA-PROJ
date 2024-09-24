#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

int main(int argc, char** argv){
    
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

    

    DEBUG_PRINT("Interface: " << cliArgs->interface << std::endl);
    DEBUG_PRINT("Sort by packets: " << cliArgs->sortPackets << std::endl);
    DEBUG_PRINT("Sort by bytes: " << cliArgs->sortBytes << std::endl);
    DEBUG_PRINT("List interfaces: " << cliArgs->printInterfaces << std::endl);

    std::cout << sniffer->getParser()->getInterface() << std::endl;
    return EXIT_SUCCESS;
}

