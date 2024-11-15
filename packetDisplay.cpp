/**
 * @file packetDisplay.cpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Implementation of the packet display class and its functions
 */

#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    initscr();
    curs_set(0);
    getmaxyx(stdscr, this->mainWinHeight, this->mainWinWidth);

    //Get the width for the subwindows based on the main window width
    int biggerWinWidth = int (this->mainWinWidth/4);
    int smallerWinWidth = int (this->mainWinWidth/6);

    //Represents the width of window for drawing
    int windowShift = biggerWinWidth;

    //Create window for source IP and port
    this->srcIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, 0);

    //Create window for destination IP and port
    this->dstIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, windowShift);
    windowShift += biggerWinWidth;

    //Create window for protocol
    this->proto = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
    windowShift += smallerWinWidth;

    //Create window for received data
    this->rx = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
    windowShift += smallerWinWidth;

    //Create window for transmitted data
    this->tx = newwin(this->mainWinHeight, smallerWinWidth, 0,  windowShift);
}     

packetDisplay::~packetDisplay(){

    //Delete all subwindows
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

    //End ncurses
    endwin();
}

void packetDisplay::clearScreen(){
    clear();
    refresh();
}

void packetDisplay::printTextCenter(WINDOW* win, int rowPos, const char* text, textType type){

    //Obtain the width of the window
    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);
    int middlePos = 0;

    //Obtain position  on which the text should be printed
    if(type == CLASSIC){
        middlePos = (winWidth - strlen(text))/2;
    } else if(type == BYTES){
        middlePos = (winWidth/2 - strlen(text)) /2;
    } else {
        middlePos = ((winWidth/2 - strlen(text)) /2) + winWidth/2;
    }

    //Print the text on specified row position
    mvwaddstr(win, rowPos, middlePos, text);

}

void packetDisplay::printHeadLineMarker(WINDOW* win){
    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);

    //Print the horizontal line through the window
    for(int i = 1; i < (winWidth - 1); i++){
        mvwaddstr(win, 2, i, "-");
    }
}

void packetDisplay::printHeadLine(){

    //Print the head line for each subwindow
    printTextCenter(this->srcIpPort, 1, "Src IP:Port", CLASSIC);
    printTextCenter(this->dstIpPort, 1, "Dst IP:Port", CLASSIC);
    printTextCenter(this->proto, 1, "Proto", CLASSIC);
    printTextCenter(this->rx, 1, "Rx", CLASSIC);
    printTextCenter(this->rx, 3, "b/s", BYTES);
    printTextCenter(this->rx, 3, "p/s", PACKETS);
    printTextCenter(this->tx, 1, "Tx", CLASSIC);
    printTextCenter(this->tx, 3, "b/s", BYTES);
    printTextCenter(this->tx, 3, "p/s", PACKETS);

    //Print the horizontal line through the subwindows
    printHeadLineMarker(this->srcIpPort);
    printHeadLineMarker(this->dstIpPort);
    printHeadLineMarker(this->proto);
    printHeadLineMarker(this->rx);
    printHeadLineMarker(this->tx);

}

void packetDisplay::printDefaultWindow(){

    //Print the border for each subwindow
    wborder(this->srcIpPort, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->dstIpPort, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->proto, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->tx, 0, 0, 0, 0, 0, 0, 0, 0);
    wborder(this->rx, 0, 0, 0, 0, 0, 0, 0, 0);

    //Print the head line
    printHeadLine();
}

void packetDisplay::printVectorConnections(std::vector<connectionInfo>& connectionVector){

    //Iterate through the vector
    for (int i = 0; i < connectionVector.size(); i++){

        //Print only first 10 connections
        if(i == 10){
            break;
        }

        
        std::string sourceIpPort;
        std::string destIpPort;

        //If src port is 0, print onl IP address
        std::string sourcePort = std::to_string(connectionVector[i].srcPort);
        if(sourcePort == "0"){
           sourceIpPort = connectionVector[i].srcIP;
        } else {
            sourceIpPort = connectionVector[i].srcIP + ":" + std::to_string(connectionVector[i].srcPort);
        }

        //If dst port is 0, print only IP address
        std::string destPort = std::to_string(connectionVector[i].dstPort);
        if(destPort == "0"){
            destIpPort = connectionVector[i].dstIP;
        } else {
            destIpPort = connectionVector[i].dstIP + ":" + std::to_string(connectionVector[i].dstPort);
        }

        //Obtain rest information from the connection
        std::string protocol = connectionVector[i].protocol;
        std::string rxPackets = std::to_string(connectionVector[i].packetsRx);
        std::string txPackets = std::to_string(connectionVector[i].packetsTx);
        std::string rxBytes = transformBytes(connectionVector[i].totalDataRx);
        std::string txBytes = transformBytes(connectionVector[i].totalDataTx);

        //Print all the information in the center of the specfic subwindow
        printTextCenter(this->srcIpPort, i+4, sourceIpPort.c_str(), CLASSIC);
        printTextCenter(this->dstIpPort, i+4, destIpPort.c_str(), CLASSIC);
        printTextCenter(this->proto, i+4, protocol.c_str(), CLASSIC);
        printTextCenter(this->rx, i+4, rxPackets.c_str(), PACKETS);
        printTextCenter(this->tx, i+4, txPackets.c_str(), PACKETS);
        printTextCenter(this->rx, i+4, rxBytes.c_str(), BYTES);
        printTextCenter(this->tx, i+4, txBytes.c_str(), BYTES);
    }

}

 std::string packetDisplay::transformBytes(long double bytes){

    std::string speed;
    long double maxBytes = 1024;
    long double maxKiloBytes = 1024 * 1024;
    long double maxMegaBytes = 1024 * 1024 * 1024;

    //Transform bytes to corret unit
    if(bytes < maxBytes){
        speed = "Bps";
        bytes = std::round(bytes * 10.0) / 10.0;
    } else if(bytes < maxKiloBytes){
        bytes /= maxBytes;
        bytes = std::round(bytes * 10.0) / 10.0;
        speed = "KBps";
    } else if(bytes < maxMegaBytes){
        bytes /= maxKiloBytes; 
        bytes = std::round(bytes * 10.0) / 10.0;
        speed = "MBps";
    } else {
        bytes /= maxMegaBytes;
        bytes = std::round(bytes * 10.0) / 10.0;
        speed = "GBps";
    }

    //Create output stream to format the bytes
    std::ostringstream out;
    out << std::fixed << std::setprecision(1) << bytes;

    //Return the formatted bytes and speed unit
    return out.str() + speed;
}

void packetDisplay::windowRefresh(std::vector<connectionInfo>& connectionVector){

    //Erase subwindow content
    werase(this->srcIpPort);
    werase(this->dstIpPort);
    werase(this->proto);
    werase(this->rx);
    werase(this->tx);

    //Print the default window
    printDefaultWindow();

    //Print the connections in the subwindows
    printVectorConnections(connectionVector);

    //Refresh the subwindows
    wrefresh(this->srcIpPort); 
    wrefresh(this->dstIpPort);
    wrefresh(this->proto);
    wrefresh(this->rx);
    wrefresh(this->tx);
    
}