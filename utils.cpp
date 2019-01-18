//
// Created by Assaf-Haik-Barouch on 18/01/2019.
//

#include "utils.h"

//converting int to string - found online
std::string numToString(int num){
    std::stringstream str1;
    str1 << num;
    std::string num_as_string = str1.str();
    return num_as_string;
}

int emitComment(std::string& comment){
    return CodeBuffer::instance().emit("#" + comment);
}

int emitComment(std::stringstream& comment){
    std::string comment_string = std::string(comment.str());
    return emitComment(comment_string);
}