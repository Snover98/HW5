//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#ifndef HW5_PARSER_CODE_H
#define HW5_PARSER_CODE_H


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "SymTable.h"
#include <vector>
#include "output.hpp"
#include <string>
#include "Node.h"
#include "bp.hpp"
#include "register_handler.h"
#include "utils.h"
#include "comparison_operators.h"
#include "func_generation.h"


//functions for enum type conversions
ExpType varToExp(VarType t);
VarType expToVar(ExpType e);

//functions for creating new scopes
void addEmptyScope();
void addFuncScope(const std::string &ID, const std::vector<FormalStruct> &formals, ExpType ret_type);
//function for removing scope
void popScope();
//function for type -> string conversion
std::string typeToString(VarType type);
//function for function -> string conversion
std::string funcToString(FunctionType &func_type);
//get function argument types vector as string
std::vector<std::string> funcArgTypes(FunctionType &func_type);
//func that adds print and printi to the symbol table
void addPrints();


//the struct types defined in the code
std::vector <std::vector<StructType> > structs_stack;
//stack of symbol tables
std::vector<SymTable> tables_stack;
//number of conditional scopes (if/else/while) we are in, used to validate break statements
unsigned int num_of_while_scopes = 0;
//var for knowing what type the current function returns
ExpType cur_ret_type = VOIDEXP;

regHandler reg_handler;


#endif //HW5_PARSER_CODE_H
