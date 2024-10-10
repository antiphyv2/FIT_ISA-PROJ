#include "packetDisplay.hpp"

packetDisplay::packetDisplay(){
    if(!setup){
        initscr();
        curs_set(0);
        getmaxyx(stdscr, this->mainWinHeight, this->mainWinWidth);

        int biggerWinWidth = int (this->mainWinWidth/4);
        int smallerWinWidth = int (this->mainWinWidth/6);

        int windowShift = biggerWinWidth;

        this->srcIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, 0);
        this->dstIpPort = newwin(this->mainWinHeight, biggerWinWidth, 0, windowShift);
        windowShift += biggerWinWidth;
        this->proto = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
        windowShift += smallerWinWidth;
        this->rx = newwin(this->mainWinHeight, smallerWinWidth, 0, windowShift);
        windowShift += smallerWinWidth;
        this->tx = newwin(this->mainWinHeight, smallerWinWidth, 0,  windowShift);
        
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

void packetDisplay::setRefreshInterval(int interval){
    this->refreshInterval = interval;
}

void packetDisplay::printTextCenter(WINDOW* win, int rowPos, const char* text, textType type){

    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);
    int middlePos = 0;


    if(type == CLASSIC){
        middlePos = (winWidth - strlen(text))/2;
    } else if(type == BYTES){
        middlePos = (winWidth/2 - strlen(text)) /2;
    } else {
        middlePos = ((winWidth/2 - strlen(text)) /2) + winWidth/2;
    }

    mvwaddstr(win, rowPos, middlePos, text);

}

void packetDisplay::printHeadLineMarker(WINDOW* win){
    int winHeight, winWidth;
    getmaxyx(win, winHeight, winWidth);
    for(int i = 1; i < (winWidth - 1); i++){
        mvwaddstr(win, 2, i, "-");
    }
}

void packetDisplay::printHeadLine(){
    printTextCenter(this->srcIpPort, 1, "Src IP:Port", CLASSIC);
    printTextCenter(this->dstIpPort, 1, "Dst IP:Port", CLASSIC);
    printTextCenter(this->proto, 1, "Proto", CLASSIC);
    printTextCenter(this->rx, 1, "Rx", CLASSIC);
    printTextCenter(this->rx, 3, "b/s", BYTES);
    printTextCenter(this->rx, 3, "p/s", PACKETS);
    printTextCenter(this->tx, 1, "Tx", CLASSIC);
    printTextCenter(this->tx, 3, "b/s", BYTES);
    printTextCenter(this->tx, 3, "p/s", PACKETS);

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
        wclear(this->srcIpPort);
        printDefaultWindow();     
        wrefresh(this->srcIpPort); 
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
    napms(this->refreshInterval);
}