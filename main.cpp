#include "main.hpp"
#include "cliparser.hpp"
#include "packetSniffer.hpp"
#include "exceptions.hpp"

//Global variable to be able to close it after signal is caught
std::unique_ptr<packetSniffer> sniffer = std::make_unique<packetSniffer>();


void gracefulExit(int signal){
    DEBUG_PRINT("CTRL+C caught, exiting sniffer..." << std::endl);
    pcap_close(sniffer->getSniffer());
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){
    
    DEBUG_PRINT("Starting isa project..." << std::endl);

    signal(SIGINT, gracefulExit);  

    std::promise<int> snifferPromise;
    std::future<int> snifferFuture = snifferPromise.get_future();
    std::thread snifferThread(&packetSniffer::runSniffer, sniffer.get(), argc, argv, std::move(snifferPromise));
    snifferThread.join();
    int result = snifferFuture.get();
    if(result != EXIT_SUCCESS){
        return result;
    }

    DEBUG_PRINT("Ending isa project..." << std::endl);

    return EXIT_SUCCESS;
}

