#include"connectionManager.hpp"

connectionManager::connectionManager(){

}
connectionManager::~connectionManager(){}

void connectionManager::addConnection(capturedPacket packet){
    // std::cout << "src IP: " << packet.srcIP << std::endl;
    // std::cout << "dst IP: " << packet.dstIP << std::endl;
    // std::cout << "src port: " << packet.srcPort << std::endl;
    // std::cout << "dst port: " << packet.dstPort << std::endl;
    // std::cout << "protocol: " << packet.protocol << std::endl;
    // std::cout << "packet length: " << packet.packetLength << std::endl;


    std::tuple mapKey = std::make_tuple(packet.srcIP, packet.dstIP, packet.srcPort, packet.dstPort, packet.protocol);
    std::tuple mapKeyReverse = std::make_tuple(packet.dstIP, packet.srcIP, packet.dstPort, packet.srcPort, packet.protocol);
    auto search = this->connectionMap.find(mapKey);
    auto searchReverse = this->connectionMap.find(mapKeyReverse);


    if(search != this->connectionMap.end()){
        this->connectionMap[mapKey].packetsTx++;
        this->connectionMap[mapKey].totalDataTx += packet.packetLength;
    } else if(searchReverse != this->connectionMap.end()){
        this->connectionMap[mapKeyReverse].packetsRx++;
        this->connectionMap[mapKeyReverse].totalDataRx += packet.packetLength;
    } else {
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
        this->connectionMap[mapKey] = newConnection;
    }
}

void connectionManager::printConnections(){
    for (auto it = this->connectionMap.begin(); it != this->connectionMap.end(); ++it) {
        std::cout << it->second.srcIP << " " << it->second.dstIP << " " << it->second.srcPort << " " << it->second.dstPort << " " << it->second.protocol << " " << it->second.packetsTx << " " << it->second.packetsRx << " " << it->second.totalDataTx << " " << it->second.totalDataRx << std::endl;
    }
}
