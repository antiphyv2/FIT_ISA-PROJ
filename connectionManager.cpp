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
    newConnection.totalDataTx = packet.packetLength;
    newConnection.packetsRx = 0;
    newConnection.totalDataRx = 0;
    this->connectionMap[forwardConnection] = newConnection;
}

void connectionManager::parseConnecionVector(){
    for(auto const& pair : this->connectionMap){
        this->connectionVector.push_back(pair.second);
    }
    this->clearConnetionMap();
}

void connectionManager::clearConnetionMap(){
    this->connectionMap.clear();
}

void connectionManager::sortConnections(sortBy sortType){
    if(sortType == BYTES || sortType == DEFAULT){
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y)
            {return y.totalDataTx > y.totalDataTx;
        });
    } else if(sortType == PACKETS){
        std::sort(this->connectionVector.begin(), this->connectionVector.end(), [](connectionInfo const& x, connectionInfo const& y){
            return x.packetsTx > y.packetsTx;
        });
    }
}

void connectionManager::printConnections(){
    // for (const auto& [key, value] : connectionMap) {
    //     // Print each key and value
    //     std::cout << "Key (Connection): ";
        
    //     // Access the elements of the key (tuple) without saving the key in a separate variable
    //     std::cout << std::get<0>(key) << ", " << std::get<1>(key) << ", ";
    //     std::cout << std::get<2>(key) << ", " << std::get<3>(key) << ", ";
    //     std::cout << std::get<4>(key) << "\n";

    //     // Access and print the value
    //     std::cout << "Packets Tx: " << value.packetsTx << ", Packets Rx: " << value.packetsRx << "\n";
    //     std::cout << "Total Data Tx: " << value.totalDataTx << ", Total Data Rx: " << value.totalDataRx << "\n";
    // }

    // for (auto const& pair : connectionMap) {
    // auto key = pair.first;
    // auto value = pair.second;
    // std::cout << std::get<0>(key) << ", " << std::get<1>(key) << ", " << value.packetsTx << ", " << value.packetsRx << ", " << value.totalDataTx << ", " << value.totalDataRx << std::endl;
    // }
}
