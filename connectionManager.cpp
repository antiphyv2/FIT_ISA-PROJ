/**
 * @file connectionManager.cpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Implementation of the connection manager functions
 */

#include"connectionManager.hpp"

connectionManager::connectionManager(){

}
connectionManager::~connectionManager(){}

void connectionManager::addConnection(connectionInfo packet, int packetLength){

    //Lock the mutex so main thread can't access the map while adding new connection
    std::lock_guard<std::mutex> lock(this->threadMutex);

    //Create forward and reverse connection tuple
    std::tuple forwardConnection = std::make_tuple(packet.srcIP, packet.dstIP, packet.srcPort, packet.dstPort, packet.protocol);
    std::tuple reverseConnection = std::make_tuple(packet.dstIP, packet.srcIP, packet.dstPort, packet.srcPort, packet.protocol);
    
    //Try to find the forward connection
    auto search = this->connectionMap.find(forwardConnection);
    if(search != this->connectionMap.end()){

        //Since it is forward connection, transmitted bytes and number of packets are increased
        this->connectionMap[forwardConnection].packetsTx++;
        this->connectionMap[forwardConnection].totalDataTx += packetLength;
        return;
    }

    //Try to find the reverse connection
    auto searchReverse = this->connectionMap.find(reverseConnection);
    if(searchReverse != this->connectionMap.end()){

        //Since it is reverse connection, received bytes and number of packets are increased
        this->connectionMap[reverseConnection].packetsRx++;
        this->connectionMap[reverseConnection].totalDataRx += packetLength;
        return;
    }

    //If the connection is not in the map, add it as a forward connection and fill the information about transmitted data
    packet.packetsTx = 1.0;
    packet.totalDataTx = packetLength;
    this->connectionMap[forwardConnection] = packet;
}

void connectionManager::parseConnecionVector(sortBy sortType){

    //Lock the mutex so sniffer thread can't access the map while sorting the connections
    std::unique_lock<std::mutex> lock(this->threadMutex);

    for(auto const& pair : this->connectionMap){
        this->connectionVector.push_back(pair.second);
    }

    //Clear the map for another iteration
    this->clearConnetionMap();

    //Unlock the mutex
    lock.unlock();

    //Sort the connections based on the sort type
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

        //Sort the connections based on the sort type using lambda function
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y)
            {return x.totalDataTx + x.totalDataRx > y.totalDataTx + y.totalDataRx;
        });
    } else if(sortType == PACKET){
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y){
            return x.packetsTx + x.packetsRx > y.packetsTx + y.packetsRx;
        });
    }
}
