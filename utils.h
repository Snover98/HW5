//
// Created by Assaf-Haik-Barouch on 18/01/2019.
//

#ifndef HW5_UTILS_H
#define HW5_UTILS_H

#include <string>
#include "bp.hpp"
#include <sstream>
#include "SymTable.h"


int emitComment(std::string comment);
int emitComment(std::stringstream& comment);
std::string numToString(int num);
int emit(std:: string str);
int emit(std::stringstream& str);
// input is number of bytes that should be added
int addPlaceInStack(int offset = 1);
int removePlaceInStack(int offset = 1);
int emitTerminate();

int funcArgsTotOffset(std::vector<FuncParam> params, SymTable& table, std::vector<std::vector<StructType> >& structs_stack);

#endif //HW5_UTILS_H
