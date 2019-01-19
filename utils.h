//
// Created by Assaf-Haik-Barouch on 18/01/2019.
//

#ifndef HW5_UTILS_H
#define HW5_UTILS_H

#include <string>
#include "bp.hpp"
#include <sstream>


int emitComment(std::string comment);
int emitComment(std::stringstream& comment);
std::string numToString(int num);
int emit(std:: string str);
int emit(std::stringstream& str);
// input is number of bytes that should be added
int addPlaceInStack(int offset = 1);


#endif //HW5_UTILS_H
