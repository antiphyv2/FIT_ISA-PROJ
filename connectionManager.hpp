#ifndef CONNECTION_MANAGER_HPP
#define CONNECTION_MANAGER_HPP

#include <iostream>
#include <string>

struct capturedPacket{
    std::string srcIP;
    std::string dstIP;
    uint16_t srcPort;
    uint16_t dstPort;
    std::string protocol;
    int packetLength;
};

struct connectionStatistics{
    int packetsTx;
    int packetsRx;
    int totalDataTx;
    int totalDataRx;
};

class connectionManager {
public:
    connectionManager();
    ~connectionManager();
    void addConnection(capturedPacket packet);
};


#endif