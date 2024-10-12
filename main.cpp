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
    packetDisplay* display = new packetDisplay; //nullptr; //= new packetDisplay;
    std::promise<int> snifferPromise;
    std::future<int> snifferFuture = snifferPromise.get_future();
    std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), std::move(snifferPromise), &manager);

    
    sortBy currentSortType = sniffer->getParser()->getSortType();
    if(display){
        display->setRefreshInterval(sniffer->getParser()->getRefreshInterval());
        while(snifferFlag){
            manager.parseConnecionVector(currentSortType);
            display->windowRefresh(manager.getConnectionVector());
            manager.clearConnectionVector();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    }

    snifferThread.join();

    int result = snifferFuture.get();
    if(result == EXIT_FAILURE){
        return result;
    }
    if(display != nullptr){
        delete display;
    }

    return EXIT_SUCCESS;
}

