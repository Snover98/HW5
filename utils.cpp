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

int emitComment(std::string comment){
    return emit("#" + comment);
}

int emitComment(std::stringstream& comment){
    return emitComment(comment.str());
}

int emit(std:: string str){
    return CodeBuffer::instance().emit(str);
}

int emit(std::stringstream& str){
    return emit(str.str());
}

int addPlaceInStack(int offset){
    //convert offset to bytes
    offset *= 4;
    return emit("add $sp, $sp, (-" + numToString(offset) +")");
}

int removePlaceInStack(int offset){
    //convert offset to bytes
    offset *= 4;
    return emit("add $sp, $sp, (" + numToString(offset) +")");
}