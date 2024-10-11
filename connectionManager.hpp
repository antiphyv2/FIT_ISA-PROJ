#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <map>

struct capturedPacket{
    std::string srcIP;
    std::string dstIP;
    uint16_t srcPort;
    uint16_t dstPort;
    std::string protocol;
    int packetLength;
};

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

class connectionManager {
private:
    std::map<std::tuple<std::string, std::string, uint16_t, uint16_t, std::string>, connectionInfo> connectionMap;
public:
    connectionManager();
    ~connectionManager();
    void addConnection(capturedPacket packet);
    void printConnections();
};


#endif