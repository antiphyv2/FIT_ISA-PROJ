#ifndef CLIPARSER_HPP
#define CLIPARSER_HPP

#include "main.hpp"
#include "connectionManager.hpp"


class cliParser {
private:
    std::string interface; // interface name
    sortBy sortType = UNSPECIFIED; // sorting type (bytes default)
    uint16_t refreshInterval = 1000; //interval of updating statisticss

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
     * @brief Set interface name
     * 
     * @param interface interface name
     */
    void setInterface(std::string interface);

    /**
     * @brief Prints help message
     */
    void printHelp();
};

#endif