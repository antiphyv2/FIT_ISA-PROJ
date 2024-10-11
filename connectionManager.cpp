#include"connectionManager.hpp"

connectionManager::connectionManager(){

}
connectionManager::~connectionManager(){}

void connectionManager::addConnection(capturedPacket packet){

    std::tuple forwardConnection = std::make_tuple(packet.srcIP, packet.dstIP, packet.srcPort, packet.dstPort, packet.protocol);
    std::tuple reverseConnection = std::make_tuple(packet.dstIP, packet.srcIP, packet.dstPort, packet.srcPort, packet.protocol);
    
    auto search = this->connectionMap.find(forwardConnection);
    if(search != this->connectionMap.end()){
        this->connectionMap[forwardConnection].packetsTx++;
        this->connectionMap[forwardConnection].totalDataTx += packet.packetLength;
        return;
    }
    auto searchReverse = this->connectionMap.find(reverseConnection);
    if(searchReverse != this->connectionMap.end()){
        this->connectionMap[reverseConnection].packetsRx++;
        this->connectionMap[reverseConnection].totalDataRx += packet.packetLength;
        return;
    }

    //If the connection is not in the map, create a new one
    connectionInfo newConnection;
    newConnection.srcIP = packet.srcIP; 
    newConnection.dstIP = packet.dstIP;
    newConnection.srcPort = packet.srcPort;
    newConnection.dstPort = packet.dstPort;
    newConnection.protocol = packet.protocol;
    newConnection.packetsTx = 1;
    newConnection.packetsRx = 0;
    newConnection.totalDataTx = packet.packetLength;
    newConnection.totalDataRx = 0;
    this->connectionMap[forwardConnection] = newConnection;
}

void connectionManager::printConnections(){
    for (auto it = this->connectionMap.begin(); it != this->connectionMap.end(); ++it) {
        std::cout << it->second.srcIP << " " << it->second.dstIP << " " << it->second.srcPort << " " << it->second.dstPort << " " << it->second.protocol << " " << it->second.packetsTx << " " << it->second.packetsRx << " " << it->second.totalDataTx << " " << it->second.totalDataRx << std::endl;
    }
}
