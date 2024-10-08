#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <iostream>

class packetDisplay {
private:
    bool setup = false;
    int winRows;
    int winCols;

public:
    packetDisplay();
    ~packetDisplay();
    void print();
    void windowRefresh();
    void printDefaultWindow();
    void printColumnBorder(int columnCord, int rows);
    void printHeadline();
};




#endif