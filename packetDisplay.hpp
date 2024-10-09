#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <iostream>
class packetDisplay {
private:
    bool setup = false;
    int winRows;
    int winCols;
    WINDOW* srcIpPort;
    WINDOW* dstIpPort;
    WINDOW* proto;
    WINDOW* rx;
    WINDOW* tx;


public:
    packetDisplay();
    ~packetDisplay();
    void print();
    void windowRefresh();
    void printDefaultWindow();
    void printHeadLine();
    void printHeadLineMarker(WINDOW* win);
};




#endif