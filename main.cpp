/**
 * @file main.cpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Main program file for the ISA project
 */

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


//Graceful exit function
void gracefulExit(int signal){
    snifferFlag.store(false);
    if(sniffer){
        //break the loop in the sniffer
        pcap_breakloop(sniffer->getSniffer());
    }
}

int main(int argc, char** argv){

    //Set signal handler
    signal(SIGINT, gracefulExit);  

    //Parse arguments
    try{
        sniffer->getParser()->parseArgs(argc, argv);
    } catch (const argParserException &e){
        if(e.getRetCode() == ERROR){
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        } else {
            //Help message or interface list was printed
            return EXIT_SUCCESS;
        }
    }
    
    //Create connection manager to store connections
    connectionManager manager;

    //Create packet display
    std::unique_ptr<packetDisplay> display = std::make_unique<packetDisplay>();
    
    //Create promise and future for sniffer thread to get the result
    std::promise<int> snifferPromise;
    std::future<int> snifferFuture = snifferPromise.get_future(); 

    //Create separate thread for sniffer to sniff the packets
    std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), std::move(snifferPromise), &manager, std::ref(display)); 

    //Obtain parameters from the parser
    sortBy currentSortType = sniffer->getParser()->getSortType();
    uint16_t refreshInterval = sniffer->getParser()->getRefreshInterval();

    //Set the refresh interval for the display
    display->setRefreshInterval(refreshInterval);

    //Reference time for the refresh interval
    auto referenceTime = std::chrono::system_clock::now();

    //Main loop for displaying the data
    while(snifferFlag){

        //Copy map of the connections to vector and sort it based on the current sort type
        manager.parseConnecionVector(currentSortType);

        //Refresh the window with updated data
        display->windowRefresh(manager.getConnectionVector()); 

        //Clear the connection vector
        manager.clearConnectionVector();

        //Add refresh interval to the reference time
        referenceTime += std::chrono::seconds(refreshInterval);

        //Sleep until updated reference time
        //std::this_thread::sleep_until(referenceTime);
        std::this_thread::sleep_for(std::chrono::seconds(refreshInterval));
    }

    //Wait for the sniffer thread to finish
    snifferThread.join();

    //Based on the result of the sniffer thread return the result
    int result = snifferFuture.get();
    if(result == EXIT_FAILURE){
        return result;
    }
    
    return EXIT_SUCCESS;
}

