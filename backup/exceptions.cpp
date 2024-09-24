#include "exceptions.hpp"

argParserException::argParserException(int retCode, const std::string& message) : retCode(retCode), message(message) {};

const char* argParserException::what() const noexcept {
    return message.c_str();
}

int argParserException::getRetCode() const{
    return this->retCode;
}
