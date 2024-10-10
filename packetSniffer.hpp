#ifndef PACKET_SNIFFER_HPP
#define PACKET_SNIFFER_HPP

#include "cliparser.hpp"
#include "connectionManager.hpp"
#include <pcap/pcap.h>

class packetSniffer {

private:
    cliParser parser;
    pcap_t* sniffer;
    char errbuf[PCAP_ERRBUF_SIZE];
public:
    
    packetSniffer();
    ~packetSniffer();

    /**
     * @brief Get the Parser object
     * 
     * @return cliParser* Pointer to the parser object
     */
    cliParser* getParser();


    /**
     * @brief Get the Sniffer object
     * 
     * @return pcap_t* Pointer to the sniffer object
     */
    pcap_t* getSniffer();

        /**
     * @brief Runs the sniffer
     * 
     */
    void runSniffer(std::promise<int> promise, connectionManager* manager);

    /**
     * @brief Sniffs the packets
     * 
     */
    void sniffThePackets(connectionManager* manager);

    /**
     * @brief Lists all available network interfaces
     * 
     */
    static void listInterfaces();

    /**
     * @brief Parses the packets 
     * 
     * @param user Pointer to the user data
     * @param pkthdr Pointer to the packet time stamp and lengths
     * @param packet Pointer to the first caplen bytes of packet data
     */
    static void packetParser(u_char* user, const struct pcap_pkthdr* pkthdr, const u_char* packet);




};
#endif