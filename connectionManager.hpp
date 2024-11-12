#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <mutex>
#include <algorithm>


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
    ulong packetsTx;
    ulong packetsRx;
    long double totalDataTx;
    long double totalDataRx;
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
    std::mutex threadMutex;
public:
    connectionManager();
    ~connectionManager();
    void addConnection(connectionInfo packet, int packetLength);
    void parseConnecionVector(sortBy sortType);
    void sortConnections(sortBy sortType);
    void clearConnetionMap();
    std::vector<connectionInfo>& getConnectionVector();
    void clearConnectionVector();
};

#endif