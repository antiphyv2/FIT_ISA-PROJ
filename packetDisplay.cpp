#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    initscr();
    curs_set(0);
    getmaxyx(stdscr, this->mainWinHeight, this->mainWinWidth);

    int biggerWinWidth = int (this->mainWinWidth/4);
    int smallerWinWidth = int (this->mainWinWidth/6);

    int windowShift = biggerWinWidth;

    this->srcIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, 0);
    this->dstIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, windowShift);
    windowShift += biggerWinWidth;
    this->proto = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
    windowShift += smallerWinWidth;
    this->rx = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
    windowShift += smallerWinWidth;
    this->tx = newwin(this->mainWinHeight, smallerWinWidth, 0,  windowShift);
}     

packetDisplay::~packetDisplay(){
    if(this->srcIpPort){
        delwin(this->srcIpPort);
    }

    if(this->dstIpPort){
        delwin(this->dstIpPort);
    }

    if(this->proto){
        delwin(this->proto);
    }

    if(this->rx){
        delwin(this->rx);
    }
    
    if(this->tx){
        delwin(this->tx);
    }
    endwin();
}

void packetDisplay::setRefreshInterval(int interval){
    this->refreshInterval = interval;
}

void packetDisplay::printTextCenter(WINDOW* win, int rowPos, const char* text, textType type){

    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);
    int middlePos = 0;


    if(type == CLASSIC){
        middlePos = (winWidth - strlen(text))/2;
    } else if(type == BYTES){
        middlePos = (winWidth/2 - strlen(text)) /2;
    } else {
        middlePos = ((winWidth/2 - strlen(text)) /2) + winWidth/2;
    }

    mvwaddstr(win, rowPos, middlePos, text);

}

void packetDisplay::printHeadLineMarker(WINDOW* win){
    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);
    for(int i = 1; i < (winWidth - 1); i++){
        mvwaddstr(win, 2, i, "-");
    }
}

void packetDisplay::printHeadLine(){
    printTextCenter(this->srcIpPort, 1, "Src IP:Port", CLASSIC);
    printTextCenter(this->dstIpPort, 1, "Dst IP:Port", CLASSIC);
    printTextCenter(this->proto, 1, "Proto", CLASSIC);
    printTextCenter(this->rx, 1, "Rx", CLASSIC);
    printTextCenter(this->rx, 3, "b/s", BYTES);
    printTextCenter(this->rx, 3, "p/s", PACKETS);
    printTextCenter(this->tx, 1, "Tx", CLASSIC);
    printTextCenter(this->tx, 3, "b/s", BYTES);
    printTextCenter(this->tx, 3, "p/s", PACKETS);

    printHeadLineMarker(this->srcIpPort);
    printHeadLineMarker(this->dstIpPort);
    printHeadLineMarker(this->proto);
    printHeadLineMarker(this->rx);
    printHeadLineMarker(this->tx);

}

void packetDisplay::printDefaultWindow(){
    wborder(this->srcIpPort, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->dstIpPort, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->proto, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->tx, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->rx, 0, 0, 0, 0, 0, 0, 0, 0);
    printHeadLine();
}

void packetDisplay::printVectorConnections(std::vector<connectionInfo>& connectionVector){
    for (int i = 0; i < connectionVector.size(); i++){
        if(i == 10){
            break;
        }
        std::string sourceIpPort = connectionVector[i].srcIP + ":" + std::to_string(connectionVector[i].srcPort);
        std::string destIpPort = connectionVector[i].dstIP + ":" + std::to_string(connectionVector[i].dstPort);
        std::string protocol = connectionVector[i].protocol;
        std::string rxPackets = std::to_string(connectionVector[i].packetsRx);
        std::string txPackets = std::to_string(connectionVector[i].packetsTx);
        printTextCenter(this->srcIpPort, i+4, sourceIpPort.c_str(), CLASSIC);
        printTextCenter(this->dstIpPort, i+4, destIpPort.c_str(), CLASSIC);
        printTextCenter(this->proto, i+4, protocol.c_str(), CLASSIC);
        printTextCenter(this->rx, i+4, rxPackets.c_str(), PACKETS);
        printTextCenter(this->tx, i+4, txPackets.c_str(), PACKETS);
    }

}

void packetDisplay::windowRefresh(std::vector<connectionInfo>& connectionVector){

    wclear(this->srcIpPort);
    wclear(this->dstIpPort);
    wclear(this->proto);
    wclear(this->rx);
    wclear(this->tx);
    printDefaultWindow();
    printVectorConnections(connectionVector);
    wrefresh(this->srcIpPort); 
    wrefresh(this->dstIpPort);
    wrefresh(this->proto);
    wrefresh(this->rx);
    wrefresh(this->tx);
    
}