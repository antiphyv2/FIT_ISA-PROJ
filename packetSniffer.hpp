/**
 * @file packetSniffer.hpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Header file defining the packet sniffer class and its functions
 */

#ifndef PACKET_SNIFFER_HPP
#define PACKET_SNIFFER_HPP

#include "cliparser.hpp"
#include "connectionManager.hpp"
#include "packetDisplay.hpp"
#include <pcap/pcap.h>

class packetSniffer {

private:
    cliParser parser;
    pcap_t* sniffer;
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
     * @param promise Promise to set the value of the sniffer
     * @param manager Pointer to the connection manager
     * @param display Reference to the packet display
     */
    void runSniffer(std::promise<int> promise, connectionManager* manager, std::unique_ptr<packetDisplay>& display);

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