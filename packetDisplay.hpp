#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <cmath>
#include <iostream>
#include <string.h>
#include <iomanip>
#include "main.hpp"
#include "connectionManager.hpp"


enum textType {
    PACKETS,
    BYTES,
    CLASSIC
};

class packetDisplay {
private:
    int refreshInterval = 1000;
    int mainWinHeight;
    int mainWinWidth;
    WINDOW* srcIpPort;
    WINDOW* dstIpPort;
    WINDOW* proto;
    WINDOW* rx;
    WINDOW* tx;

public:
    packetDisplay();
    ~packetDisplay();
    void print();
    void windowRefresh(std::vector<connectionInfo>& connectionVector);
    void printDefaultWindow();
    void printHeadLine();
    void printHeadLineMarker(WINDOW* win);
    void printTextCenter(WINDOW* win, int rowPos, const char* text, textType type);
    void setRefreshInterval(int interval);

    void printVectorConnections(std::vector<connectionInfo>& connectionVector);
    std::string transformBytes(long double bytes);
};

#endif