#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"
#include "packetDisplay.hpp"

//Atomic flag to be able to close the sniffer
std::atomic<bool> snifferFlag(true);

//Global variable to be able to close it after signal is caught

void gracefulExit(int signal){
    snifferFlag.store(false);

}

int main(int argc, char** argv){
    // std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();
    // DEBUG_PRINT("Starting isa project..." << std::endl);

    // signal(SIGINT, gracefulExit);  

    // std::promise<int> snifferPromise;
    // std::future<int> snifferFuture = snifferPromise.get_future();
    // std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), argc, argv, std::move(snifferPromise));
    // snifferThread.join();
    // int result = snifferFuture.get();
    // if(result != EXIT_SUCCESS){
    //     return result;
    // }

    std::unique_ptr<packetDisplay> display = std::make_unique<packetDisplay>();
    while(true){
        display->windowRefresh();
    }
    

    DEBUG_PRINT("Ending isa project..." << std::endl);

    return EXIT_SUCCESS;
}

