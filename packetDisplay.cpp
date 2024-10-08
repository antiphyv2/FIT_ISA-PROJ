#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    if(!setup){
        initscr();
        setup = true;
    }
}

packetDisplay::~packetDisplay(){
    endwin();
}

void packetDisplay::printColumnBorder(int columnCord, int rows){
    for(int j = 1; j < rows; j++){
        mvaddstr(j, columnCord, "|");
    }
}

void packetDisplay::printHeadline(){
    mvaddstr(1, 17, "SRC IP:PORT");
    mvaddstr(1, 63, "DST IP:PORT");
    mvaddstr(1, 98, "PROTO");
    mvaddstr(1, 118, "Rx");
    mvaddstr(1, 138, "Tx");
}

void packetDisplay::print(){
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    for(int i = 0; i < cols; i++){
        mvaddstr(0, i, "-");
        mvaddstr(2, i, "-");
        mvaddstr(rows - 1, i, "-");
        if(i == 0 || i == 45 || i == 91 || i == 109 || i == 129 || i == 149 || i == (cols - 1)){
            printColumnBorder(i, rows);
        }
    }
    printHeadline();
    // wprintw(leftwindow, "hello world");
    // wrefresh(leftwindow);
    refresh();
}

void packetDisplay::windowRefresh(){
    clear();
    print();
    //refresh();
    napms(1000);
}