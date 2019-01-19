//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#ifndef HW5_FUNC_GENERATION_H
#define HW5_FUNC_GENERATION_H

#include <string>
#include "utils.h"
#include "SymTable.h"
#include "register_handler.h"

// emit label for function code + comments
int emitFuncStart(std::string& func_name);
// setup function call BEFORE pushing arguments into the stack in order
int emitSetupFuncCall(std::string& func_name, SymTable& table);
// make sure $sp is the correct value before starting to push function arguments
int updateSPBeforeCall(std::string& func_name, SymTable& table);
// save all registers in stack
int emitSaveRegisters();
// function for pushing value in the register into the stack
int emitPushReg(int reg_num);
//function for popping registers from stack
int emitLoadRegisters();
//function for pooping a value into a register
int emitPopReg(int reg_num);



#endif //HW5_FUNC_GENERATION_H
