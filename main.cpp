#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"
#include "packetDisplay.hpp"
#include "connectionManager.hpp"

//Atomic flag to be able to close the sniffer
std::atomic<bool> snifferFlag(true);

//Global sniffer pointer to be able to call breakloop in the signal handler
std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();


//graceful exit function
void gracefulExit(int signal){
    snifferFlag.store(false);
    if(sniffer){
        //break the loop in the sniffer
        pcap_breakloop(sniffer->getSniffer());
    }
}

int main(int argc, char** argv){
    signal(SIGINT, gracefulExit);  

    //parse arguments
    try{
        sniffer->getParser()->parseArgs(argc, argv);
    } catch (const argParserException &e){
        if(e.getRetCode() == ERROR){
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        } else {
            return EXIT_SUCCESS;
        }
    }
    
    connectionManager manager;
    std::unique_ptr<packetDisplay> display = std::make_unique<packetDisplay>();
    
    std::promise<int> snifferPromise;
    std::future<int> snifferFuture = snifferPromise.get_future(); //create promise and future for sniffer thread to get the result
    std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), std::move(snifferPromise), &manager); //create separate thread for sniffer

    
    sortBy currentSortType = sniffer->getParser()->getSortType();
    uint16_t refreshInterval = sniffer->getParser()->getRefreshInterval();

    //main loop for displaying the data
    while(snifferFlag){
        manager.parseConnecionVector(currentSortType); //copy map of connections to vector and sort it
        display->windowRefresh(manager.getConnectionVector()); //refresh the window with updated data
        manager.clearConnectionVector();
        std::this_thread::sleep_for(std::chrono::seconds(refreshInterval)); //sleep for 
    }

    //wait for the sniffer thread to finish
    snifferThread.join();

    int result = snifferFuture.get();
    if(result == EXIT_FAILURE){
        return result;
    }
    
    return EXIT_SUCCESS;
}

