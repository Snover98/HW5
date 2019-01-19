//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#ifndef HW5_FUNC_GENERATION_H
#define HW5_FUNC_GENERATION_H

#include <string>
#include "utils.h"
#include "SymTable.h"
#include "register_handler.h"

//emit code for returning from a function
int emitReturn(int reg_num = -1);

// emit label for function code + comments
int emitFuncStart(std::string &func_name);

// setup function call BEFORE pushing arguments into the stack in order
int emitSetupFuncCall(std::string &func_name, SymTable &table);

// make sure $sp is the correct value before starting to push function arguments
int updateSPBeforeCall(std::string &func_name, SymTable &table);

// save all registers in stack
int emitSaveRegisters();

// function for pushing value in the register into the stack
int emitPushReg(int reg_num);

//function for popping registers from stack
int emitLoadRegisters();

//function for pooping a value into a register
int emitPopReg(int reg_num);

//load variable from stack into register, offset is in number of bytes
int emitLoadVar(int reg_num, int offset);

//save variable from register into stack, offset is in number of bytes
int emitSaveVar(int reg_num, int offset);

//load & save var with ID and symbol table
int emitLoadVar(int reg_num, std::string &ID, SymTable &table);

int emitSaveVar(int reg_num, std::string &ID, SymTable &table);

//functions for struct fields
int emitLoadStructField(int reg_num, std::string &struct_name, std::string &field_name, SymTable &table, StructType &t);

int emitSaveStructField(int reg_num, std::string &struct_name, std::string &field_name, SymTable &table, StructType &t);

int emitLoadStructField(int reg_num, int offset, std::string &field_name, SymTable &table, StructType &t);

int emitSaveStructField(int reg_num, int offset, std::string &field_name, SymTable &table, StructType &t);

//function for struct1 = struct2
int emitStructsEq(int offset1, int offset2, StructType& t, regHandler& r);

int emitStructsEq(std::string &struct1, std::string &struct2, SymTable &table, StructType &t, regHandler &r);

//done after setup & pushing arguments into stack
int emitFuncCall(std::string func_name, SymTable& table, std::vector<std::vector<StructType> > &structs_stack);

#endif //HW5_FUNC_GENERATION_H
