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

void packetDisplay::printDefaultWindow(){
    getmaxyx(stdscr, this->winRows, this->winCols);
    for(int i = 0; i < winCols; i++){
        mvaddstr(0, i, "-");
        mvaddstr(2, i, "-");
        mvaddstr(winRows - 1, i, "-");
        if(i == 0 || i == 45 || i == 91 || i == 109 || i == 129 || i == 149 || i == (winCols - 1)){
            printColumnBorder(i, winRows);
        }
    }
    printHeadline();
    refresh();
}
void packetDisplay::print(){

}

void packetDisplay::windowRefresh(){
    clear();
    printDefaultWindow();
    //refresh();
    napms(1000);
}