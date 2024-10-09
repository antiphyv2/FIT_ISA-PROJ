#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    if(!setup){
        initscr();
        curs_set(0);
        getmaxyx(stdscr, this->winRows, this->winCols);

        int biggerWinWidth = int (this->winCols/4);
        int smallerWinWidth = int (this->winCols/6);

        int windowShift = biggerWinWidth;

        this->srcIpPort = newwin(this->winRows, biggerWinWidth, 0, 0);
        this->dstIpPort = newwin(this->winRows, biggerWinWidth, 0, windowShift);
        windowShift += biggerWinWidth;
        this->proto = newwin(this->winRows, smallerWinWidth, 0, windowShift);
        windowShift += smallerWinWidth;
        this->rx = newwin(this->winRows, smallerWinWidth, 0, windowShift);
        windowShift += smallerWinWidth;
        this->tx = newwin(this->winRows, smallerWinWidth, 0,  windowShift);
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

void packetDisplay::printTextCenter(WINDOW* win, int rowPos, const char* text){
    int rows, cols;
    getmaxyx(win, rows, cols);
    int middlePos = (cols - strlen(text))/2;
    mvwaddstr(win, rowPos, middlePos, text);
}

void packetDisplay::printHeadLineMarker(WINDOW* win){
    int rows, cols;
    getmaxyx(win, rows, cols);
    for(int i = 1; i < (cols - 1); i++){
        mvwaddstr(win, 2, i, "-");
    }
}

void packetDisplay::printHeadLine(){
    printTextCenter(this->srcIpPort, 1, "Src IP:Port");
    printTextCenter(this->dstIpPort, 1, "Dst IP:Port");
    printTextCenter(this->proto, 1, "Proto");
    printTextCenter(this->rx, 1, "Rx");
    printTextCenter(this->rx, 3, "b/s p/s");
    printTextCenter(this->tx, 1, "Tx");
    printTextCenter(this->tx, 3, "b/s p/s");

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