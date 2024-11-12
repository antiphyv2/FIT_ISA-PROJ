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

/**
 * @brief Enum for type of sorting
 * 
 */
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

    //Map for storing the connections
    std::map<std::tuple<std::string, std::string, uint16_t, uint16_t, std::string>, connectionInfo> connectionMap;

    //Vector for storing the connections to be displayed
    std::vector<connectionInfo> connectionVector;

    //Mutex for thread safety (sniffer and main thread)
    std::mutex threadMutex;
public:
    connectionManager();
    ~connectionManager();

    /**
     * @brief Add a new connection to the map
     * 
     * @param packet new packet to be added
     * @param packetLength packet length obtained from the sniffer
     */
    void addConnection(connectionInfo packet, int packetLength);

    /**
     * @brief Copies all connections from the map to the vector, clears the map and sorts the vector based on the sort type
     * 
     * @param sortType sorting type for the connections
     */
    void parseConnecionVector(sortBy sortType);

    /**
     * @brief Sorts the connections in the connection vector based on the sort type
     * 
     * @param sortType sorting type for the connections
     */
    void sortConnections(sortBy sortType);

    /**
     * @brief Clears the connection map
     * 
     */
    void clearConnetionMap();

    /**
     * @brief Returns the connection vector
     * 
     * @return std::vector<connectionInfo>& connection vector
     */
    std::vector<connectionInfo>& getConnectionVector();

    /**
     * @brief Clears the connection vector
     * 
     */
    void clearConnectionVector();
};

#endif