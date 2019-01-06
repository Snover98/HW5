//
// Created by Assaf-Haik-Barouch on 12/12/2018.
//

#ifndef HW3_EXCEPTIONS_H
#define HW3_EXCEPTIONS_H

#include <exception>
#include <string>

class ShadowingException : public std::exception{
public:
    const std::string overriden_ID;

    ShadowingException(const std::string ID) : std::exception(), overriden_ID(std::string(ID)){}

    ~ShadowingException() throw() {}

    const char * what () const throw (){
        return std::string("errorDef: Tried to shadow identifier " + overriden_ID).c_str();
    }
};

#endif //HW3_EXCEPTIONS_H
