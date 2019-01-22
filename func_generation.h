//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#ifndef HW5_FUNC_GENERATION_H
#define HW5_FUNC_GENERATION_H

#include <string>
#include "utils.h"
#include "SymTable.h"
#include "register_handler.h"

//emit code for returning from a function, if reg_num == -1, this is for a function with no return value
int emitReturn(int reg_num = -1);

// emit label for function code + comments
int emitFuncStart(std::string func_name);

//emit ending of the function
int emitFuncEnd(std::string func_name);

// setup function call BEFORE pushing arguments into the stack in order
int emitSetupFuncCall(std::string func_name, SymTable &table, regHandler &r);

// make sure $sp is the correct value before starting to push function arguments
int updateSPBeforeCall(SymTable &table);

// save all registers in stack
int emitSaveRegisters(regHandler &r);

// function for pushing value in the register into the stack
int emitPushReg(int reg_num);

// function for pushing an expression into the stack
int pushExp(Expression* exp, regHandler& r, std::vector<std::vector<StructType> > &structs_stack);

//function for popping registers from stack
int emitLoadRegisters(regHandler &r);

//function for pooping a value into a register
int emitPopReg(int reg_num);

//load variable from stack into register, offset is in number of bytes
int emitLoadVar(int reg_num, int offset);

//save variable from register into stack, offset is in number of bytes
int emitSaveVar(int reg_num, int offset);

//load & save var with ID and symbol table
int emitLoadVar(int reg_num, std::string &ID, std::vector<SymTable> &tables);

int emitSaveVar(int reg_num, std::string &ID, std::vector<SymTable> &tables);

//functions for struct fields
int emitLoadStructField(int reg_num, std::string &struct_name, std::string &field_name, std::vector<SymTable> &tables, StructType t);

int emitSaveStructField(int reg_num, std::string &struct_name, std::string &field_name, std::vector<SymTable> &tables, StructType t);

int emitLoadStructField(int reg_num, int offset, std::string &field_name, std::vector<SymTable> &tables, StructType t);

int emitSaveStructField(int reg_num, int offset, std::string &field_name, std::vector<SymTable> &tables, StructType t);

//function for struct1 = struct2
int emitStructsEq(int offset1, int reg2, StructType t, regHandler &r);

int emitStructsEq(std::string &struct1, int reg2, std::vector<SymTable> &tables, StructType t, regHandler &r);

//done after setup & pushing arguments into stack
int emitFuncCall(std::string func_name, std::vector<SymTable> &tables, std::vector<std::vector<StructType> > &structs_stack,
                 regHandler &r);

int saveDefaultVal(int offset, regHandler &r);

#endif //HW5_FUNC_GENERATION_H
