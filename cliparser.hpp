#ifndef CLIPARSER_HPP
#define CLIPARSER_HPP

#include "main.hpp"


class cliParser {
private:
    std::string interface; // interface name
    bool sortPackets = false; // sort output by number of packets
    bool sortBytes = false; // sort output by number of bytes

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
     * @brief Get sort by packets flag
     * 
     * @return bool sort by packets flag
     */
    bool getSortPackets();

    /**
     * @brief Get sort by bytes flag
     * 
     * @return bool sort by bytes flag
     */
    bool getSortBytes();

    /**
     * @brief Set interface name
     * 
     * @param interface interface name
     */
    void setInterface(std::string interface);

    /**
     * @brief Set sort by packets flag
     * 
     * @param sortPackets sort by packets flag
     */
    void setSortPackets(bool sortPackets);

    /**
     * @brief Set sort by bytes flag
     * 
     * @param sortBytes sort by bytes flag
     */
    void setSortBytes(bool sortBytes);

    /**
     * @brief Prints help message
     */
    void printHelp();
};

enum parserRetCodes {
    OK,
    PRINT_HELP,
    LIST_INTERFACES,
};

#endif