#include"connectionManager.hpp"

connectionManager::connectionManager(){}
connectionManager::~connectionManager(){}

void connectionManager::addConnection(capturedPacket packet){
    std::cout << "src IP: " << packet.srcIP << std::endl;
    std::cout << "dst IP: " << packet.dstIP << std::endl;
    std::cout << "src port: " << packet.srcPort << std::endl;
    std::cout << "dst port: " << packet.dstPort << std::endl;
    std::cout << "protocol: " << packet.protocol << std::endl;
    std::cout << "packet length: " << packet.packetLength << std::endl;
}