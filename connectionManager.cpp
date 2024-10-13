#include"connectionManager.hpp"

connectionManager::connectionManager(){

}
connectionManager::~connectionManager(){}

void connectionManager::addConnection(connectionInfo packet, int packetLength){
    std::lock_guard<std::mutex> lock(this->threadMutex);

    std::tuple forwardConnection = std::make_tuple(packet.srcIP, packet.dstIP, packet.srcPort, packet.dstPort, packet.protocol);
    std::tuple reverseConnection = std::make_tuple(packet.dstIP, packet.srcIP, packet.dstPort, packet.srcPort, packet.protocol);
    
    auto search = this->connectionMap.find(forwardConnection);
    if(search != this->connectionMap.end()){
        this->connectionMap[forwardConnection].packetsTx++;
        this->connectionMap[forwardConnection].totalDataTx += packetLength;
        return;
    }
    auto searchReverse = this->connectionMap.find(reverseConnection);
    if(searchReverse != this->connectionMap.end()){
        this->connectionMap[reverseConnection].packetsRx++;
        this->connectionMap[reverseConnection].totalDataRx += packetLength;
        return;
    }

    //If the connection is not in the map, add it and fill information about transmitted data
    packet.packetsTx = 1;
    packet.totalDataTx = packetLength;
    this->connectionMap[forwardConnection] = packet;
}

void connectionManager::parseConnecionVector(sortBy sortType){
    std::unique_lock<std::mutex> lock(this->threadMutex);

    for(auto const& pair : this->connectionMap){
        this->connectionVector.push_back(pair.second);
    }
    //this->clearConnetionMap();
    lock.unlock();

    sortConnections(sortType);
}

void connectionManager::clearConnetionMap(){
    this->connectionMap.clear();
}

std::vector<connectionInfo>& connectionManager::getConnectionVector() {
    return this->connectionVector;
}

void connectionManager::clearConnectionVector(){
    this->connectionVector.clear();
}

void connectionManager::sortConnections(sortBy sortType){
    if(sortType == BYTE || sortType == UNSPECIFIED){
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y)
            {return x.totalDataTx + x.totalDataRx > y.totalDataTx + y.totalDataRx;
        });
    } else if(sortType == PACKET){
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y){
            return x.packetsTx + x.packetsRx > y.packetsTx + y.packetsRx;
        });
    }
}
