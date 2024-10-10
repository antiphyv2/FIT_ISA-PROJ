#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"
#include "packetDisplay.hpp"
#include "connectionManager.hpp"

//Atomic flag to be able to close the sniffer
std::atomic<bool> snifferFlag(true);
std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();
//Global variable to be able to close it after signal is caught


void gracefulExit(int signal){
    snifferFlag.store(false);
    if(sniffer){
        pcap_breakloop(sniffer->getSniffer());
    }
}

int main(int argc, char** argv){
    signal(SIGINT, gracefulExit);  
    DEBUG_PRINT("Starting isa project..." << std::endl);
    
    //std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();

    try{
        sniffer->getParser()->parseArgs(argc, argv);
    } catch (const argParserException &e){
        if(e.getRetCode() != PRINT){
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
    }
    
    connectionManager manager;
    packetDisplay* display = nullptr; //= new packetDisplay;
    //std::unique_ptr<packetDisplay> display = std::make_unique<packetDisplay>();
    std::promise<int> snifferPromise;
    std::future<int> snifferFuture = snifferPromise.get_future();
    std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), std::move(snifferPromise), &manager, display);

    
    
    
    //display->setRefreshInterval(sniffer->getParser()->getRefreshInterval());
    //display->windowRefresh();

    snifferThread.join();
    if(display){
        delete display;
    }
    
    int result = snifferFuture.get();
    if(result != EXIT_SUCCESS){
        return result;
    }

    // std::unique_ptr<packetDisplay> display = std::make_unique<packetDisplay>();
    // display->setRefreshInterval(sniffer->getParser()->getRefreshInterval());
    // while(true){
    //     display->windowRefresh();
    // }
    
    DEBUG_PRINT("Ending isa project..." << std::endl);
    return EXIT_SUCCESS;
}

