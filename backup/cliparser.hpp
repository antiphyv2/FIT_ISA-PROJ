#ifndef CLIPARSER_HPP
#define CLIPARSER_HPP

#include "main.hpp"


//Structure to store parsed cli arguments
struct parsedArgs {
    std::string interface; // interface name
    bool sortPackets = false; // sort output by number of packets
    bool sortBytes = false; // sort output by number of bytes
    bool printInterfaces = false; // interface list will be printed if true
};

class cliParser {
public:
    /**
     * @brief Do parse arguments from command line and stores them into parsedArgs structure
     * 
     * @param argc number of arguments
     * @param argv array of arguments
     * @param cliArgs structure where parsed arguments will be stored
     */
    static void parseArgs(int argc, char** argv, parsedArgs& argStruct);
};

#endif