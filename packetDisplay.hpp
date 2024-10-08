#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <iostream>

class packetDisplay {
private:
    bool setup = false;
    WINDOW* leftwindow;

public:
    packetDisplay();
    ~packetDisplay();
    void print();
    void windowRefresh();
    void printColumnBorder(int columnCord, int rows);
    void printHeadline();
};




#endif