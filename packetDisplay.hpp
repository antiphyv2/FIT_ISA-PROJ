#ifndef PACKET_DISPLAY_HPP
#define PACKET_DISPLAY_HPP

#include <ncurses.h>
#include <cmath>
#include <iostream>
#include <string.h>
#include <iomanip>
#include "main.hpp"
#include "connectionManager.hpp"


/**
 * @brief Enum for text type useful for printing text in the center of the window
 * 
 */
enum textType {
    PACKETS,
    BYTES,
    CLASSIC
};

class packetDisplay {
private:
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

    /**
     * @brief Refreshes the main window with all subwindows with updated data
     * 
     * @param connectionVector vector of connections to be displayed
     */
    void windowRefresh(std::vector<connectionInfo>& connectionVector);

    /**
     * @brief Creates the main window and all subwindows
     * 
     */
    void printDefaultWindow();

    /**
     * @brief Prints the headline for each subwindow
     * 
     */
    void printHeadLine();

    /**
     * @brief Prints the headline marker for each subwindow
     * 
     * @param win subwindow where marker is printed
     */
    void printHeadLineMarker(WINDOW* win);

    /**
     * @brief Prints text in the center of given window on specified row position
     * 
     * @param win window where the text is printed
     * @param rowPos row position where the text is printed
     * @param text text to be printed
     * @param type type of text to be printed
     */
    void printTextCenter(WINDOW* win, int rowPos, const char* text, textType type);

    /**
     * @brief Prints vector of connections in correct subwindows
     * 
     * @param connectionVector vector of connections
     */
    void printVectorConnections(std::vector<connectionInfo>& connectionVector);

    /**
     * @brief Transforms number of bytes to human readable format with speed unit
     * 
     * @param bytes number of bytes
     * @return std::string readable format of bytes to be displayed
     */
    std::string transformBytes(long double bytes);
};

#endif