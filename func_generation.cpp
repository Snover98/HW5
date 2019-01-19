//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#include "func_generation.h"


int emitFuncStart(std::string& func_name){
    emitComment("CODE OF FUNCTION " + func_name);
    return emit(func_name + ":");
}

int emitSetupFuncCall(std::string& func_name, SymTable& table){
    //save all registers in stack
    emitComment("SAVING REGISTERS");
    emitSaveRegisters();

    //save old fp and ra
    addPlaceInStack();
    emit("sw $fp, ($sp)");
    addPlaceInStack();
    return emit("sw $ra, ($sp)");
    //after this the arguments should be put in the stack
}

int updateSPBeforeCall(std::string& func_name, SymTable& table){
    emitComment("update $sp according to the symbol table");
    return emit("add $sp, $fp, (-" + numToString(table.nextOffset()) +")");
}

int emitSaveRegisters(){
    int last_command = -1;
    for(int i=0; i<NUM_OF_REGISTERS; ++i){
        last_command = emitPushReg(i);
    }

    return last_command;
}

int emitPushReg(int reg_num){
    addPlaceInStack();
    return emit("sw " + regName(reg_num) +", ($sp)");
}

int emitLoadRegisters(){
    int last_command = -1;
    for(int i=NUM_OF_REGISTERS-1; i>=0; --i){
        last_command = emitPopReg(i);
    }

    return last_command;
}

int emitPopReg(int reg_num){
    emit("lw " + regName(reg_num) +", ($sp)");
    return removePlaceInStack();
}

int emitLoadVar(int reg_num, int offset){
    offset *= 4;
    return emit("lw " + regName(reg_num) + ", " + numToString(-offset) + "($fp)");
}

int emitSaveVar(int reg_num, int offset){
    offset *= 4;
    return emit("sw " + regName(reg_num) + ", " + numToString(-offset) + "($fp)");
}

int emitLoadVar(int reg_num, std::string& ID, SymTable& table){
    emitComment("load the variable " + ID + "into the register " + regName(reg_num));
    return emitLoadVar(reg_num, table.getSymbolEntry(ID).offset);
}

int emitSaveVar(int reg_num, std::string& ID, SymTable& table){
    emitComment("save the variable " + ID + "from the register " + regName(reg_num) + "into the stack");
    return emitSaveVar(reg_num, table.getSymbolEntry(ID).offset);
}

