#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <iostream>
#include <string.h>


enum textType {
    PACKETS,
    BYTES,
    CLASSIC
};

class packetDisplay {
private:
    bool setup = false;
    int mainWinHeight;
    int mainWinWidth;
    WINDOW* srcIpPort;
    WINDOW* dstIpPort;
    WINDOW* proto;
    WINDOW* rx;
    WINDOW* tx;
    WINDOW* rxBs;
    WINDOW* rxPs;
    WINDOW* txBs;
    WINDOW* txPs;


public:
    packetDisplay();
    ~packetDisplay();
    void print();
    void windowRefresh();
    void printDefaultWindow();
    void printHeadLine();
    void printHeadLineMarker(WINDOW* win);
    void printTextCenter(WINDOW* win, int rowPos, const char* text, textType type);
};

#endif