#include "exceptions.hpp"

argParserException::argParserException(int retCode, const std::string& message) : retCode(retCode), message(message) {};

const char* argParserException::what() const noexcept {
    return message.c_str();
}

int argParserException::getRetCode() const{
    return this->retCode;
}

packetSnifferException::packetSnifferException(int retCode, const std::string& message) : retCode(retCode), message(message) {};

const char* packetSnifferException::what() const noexcept {
    return message.c_str();
}

int packetSnifferException::getRetCode() const{
    return this->retCode;
}
