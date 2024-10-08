#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    if(!setup){
        initscr();
        curs_set(0);
        getmaxyx(stdscr, this->winRows, this->winCols);
        this->srcIpPort = newwin(this->winRows, 45, 0, 0);
        this->dstIpPort = newwin(this->winRows, 45, 0, 45);
        this->proto = newwin(this->winRows, 19, 0, 90);
        this->rx = newwin(this->winRows, 20, 0, 109);
        this->tx = newwin(this->winRows, 20, 0, 129);
        setup = true;
    }
}

packetDisplay::~packetDisplay(){
    delwin(this->srcIpPort);
    delwin(this->dstIpPort);
    delwin(this->proto);
    delwin(this->rx);
    delwin(this->tx);
    endwin();
}

void packetDisplay::printHeadLineMarker(WINDOW* win){
    int rows, cols;
    getmaxyx(win, rows, cols);
    for(int i = 1; i < (cols - 1); i++){
        mvwaddstr(win, 2, i, "-");
    }
}

void packetDisplay::printHeadLine(){
    mvwaddstr(this->srcIpPort, 1, 17, "SRC IP:PORT");
    mvwaddstr(this->dstIpPort, 1, 17, "DST IP:PORT");
    mvwaddstr(this->proto, 1, 7, "PROTO");
    mvwaddstr(this->rx, 1, 9, "Rx");
    mvwaddstr(this->tx, 1, 9, "Tx");

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
void packetDisplay::print(){

}

void packetDisplay::windowRefresh(){

    if (this->srcIpPort != nullptr) {
        wclear(this->srcIpPort);  // Clear if necessary
        printDefaultWindow();     // Redraw window
        wrefresh(this->srcIpPort); // Refresh after update
    }

    if (this->dstIpPort != nullptr) {
        wclear(this->dstIpPort);
        printDefaultWindow();
        wrefresh(this->dstIpPort);
    }

    if (this->proto != nullptr) {
        wclear(this->proto);
        printDefaultWindow();
        wrefresh(this->proto);
    }

    if (this->rx != nullptr) {
        wclear(this->rx);
        printDefaultWindow();
        wrefresh(this->rx);
    }

    if (this->tx != nullptr) {
        wclear(this->tx);
        printDefaultWindow();
        wrefresh(this->tx);
    }
    napms(1000);
}