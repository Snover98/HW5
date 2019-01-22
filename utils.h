//
// Created by Assaf-Haik-Barouch on 18/01/2019.
//

#ifndef HW5_UTILS_H
#define HW5_UTILS_H

#include <string>
#include "bp.hpp"
#include <sstream>
#include "SymTable.h"
#include <map>
#include "register_handler.h"
#include "Node.h"

static int num_strings = 0;
static std::map<std::string, std::string> string_labels;

int emitComment(std::string comment);
int emitComment(std::stringstream& comment);
std::string numToString(int num);
int emit(std:: string str);
int emit(std::stringstream& str);
// input is number of bytes that should be added
int addPlaceInStack(int offset = 1);
int removePlaceInStack(int offset = 1);
int emitTerminate();
int emitDivByZeroCheck(int reg, std::string& handler_label);
//returns the label of the handler
std::string emitDivByZeroHandler();

//puts the result of a boolean expression in a register
int emitSaveBoolRes(Expression* bool_exp, int reg);

int funcArgsTotOffset(std::vector<FuncParam> params, std::vector<std::vector<StructType> >& structs_stack);
std::string strData(std::string str);

int getExpReg(Expression* exp, regHandler& r);

#endif //HW5_UTILS_H
