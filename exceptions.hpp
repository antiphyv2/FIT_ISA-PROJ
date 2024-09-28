#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP
#include "main.hpp"


class argParserException : public std::exception {
private:
    int retCode;
    std::string message;
    
public:
    /**
     * @brief Exception constructor
     * 
     * @param retCode return code
     * @param message message of the exception
     */
    argParserException(int retCode, const std::string& message);

    /**
     * @brief Returns the message of the exception
     * 
     * @return const char* message of the exception
     */
    const char* what() const noexcept override;

    /**
     * @brief Gets the return code of the exception
     * 
     * @return int error code
     */
    int getRetCode() const;
};

class packetSnifferException : public std::exception {
private:
    int retCode;
    std::string message;

public:
    /**
     * @brief Exception constructor
     * 
     * @param retCode return code
     * @param message message of the exception
     */
    packetSnifferException(int retCode, const std::string& message);

    /**
     * @brief Returns the message of the exception
     * 
     * @return const char* message of the exception
     */
    const char* what() const noexcept override;

    /**
     * @brief Gets the return code of the exception
     * 
     * @return int error code
     */
    int getRetCode() const;
};

enum parserExcCodes {
    ERROR,
    PRINT,
    DEFAULT,
};

enum snifferRetCodes {
    INTERFACE_ERROR,
    PACKET_ERROR,
    SNIFFER_OK,
    SNIFFER_ERROR
};
#endif