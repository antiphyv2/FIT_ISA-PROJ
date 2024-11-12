/**
 * @file cliparser.hpp
 * @author Samuel Hejnicek (xhejni00)
 * @brief Header file defining functions for parsing command line arguments
 */

#ifndef CLIPARSER_HPP
#define CLIPARSER_HPP

#include "main.hpp"
#include "connectionManager.hpp"


class cliParser {
private:

    //Interface name
    std::string interface; 

    //Sorting type (bytes default)
    sortBy sortType = UNSPECIFIED; 

    //Default interval (s) of updating statistics
    uint16_t refreshInterval = 1; 

public:
    /**
     * @brief Do parse arguments from command line and stores them into parsedArgs structure
     * 
     * @param argc number of arguments
     * @param argv array of arguments
     */
    void parseArgs(int argc, char** argv);

    /**
     * @brief Get interface name
     * 
     * @return std::string interface name
     */
    std::string getInterface();

    /**
     * @brief Get the sort type
     * 
     * @return sortBy type of sorting
     */
    sortBy getSortType();

    /**
     * @brief Get interval of refreshing window
     * 
     * @return int time interval
     */
    int getRefreshInterval();

    /**
     * @brief Prints help message
     */
    void printHelp();
};

#endif