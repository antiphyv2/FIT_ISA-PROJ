#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <vector>

/**
 * @brief Structure for parsed packet from the sniffer
 * 
 */
struct capturedPacket{
    std::string srcIP;
    std::string dstIP;
    uint16_t srcPort;
    uint16_t dstPort;
    std::string protocol;
    int packetLength;
};

/**
 * @brief Structure for connection stats like packets or bytes sent or received
 * 
 */
struct connectionInfo{
    std::string srcIP;
    std::string dstIP;
    uint16_t srcPort;
    uint16_t dstPort;
    std::string protocol;
    int packetsTx;
    int packetsRx;
    int totalDataTx;
    int totalDataRx;
};

enum sortBy {
    BYTE,
    PACKET,
    UNSPECIFIED,
};

/**
 * @brief class for handling the connections
 * 
 */
class connectionManager {
private:
    std::map<std::tuple<std::string, std::string, uint16_t, uint16_t, std::string>, connectionInfo> connectionMap;
    std::vector<connectionInfo> connectionVector;
public:
    connectionManager();
    ~connectionManager();
    void addConnection(capturedPacket packet);
    void printConnections();
    void parseConnecionVector(sortBy sortType);
    void sortConnections(sortBy sortType);
    void clearConnetionMap();
    void clearConnectionVector();
};

#endif