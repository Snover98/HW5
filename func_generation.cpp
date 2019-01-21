//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#include "func_generation.h"
#include <limits.h>


int emitFuncStart(std::string func_name) {
    emitComment("CODE OF FUNCTION " + func_name);
    emit(".globl " + func_name);
    emit(".ent " + func_name);
    return emit(func_name + ":");
}

int emitFuncEnd(std::string func_name){
    int first_command = INT_MAX;
    if(func_name == "main"){
        first_command = emitTerminate();
    }
    first_command = std::min(first_command, emit(".end " + func_name));
    emit("");
    return first_command;
}

int emitSetupFuncCall(std::string func_name, SymTable &table) {
    //make sure that $sp is correct
    int first_command = updateSPBeforeCall(func_name, table);
    //save all registers in stack
    emitComment("SAVING REGISTERS");
    emitSaveRegisters();

    //save old fp and ra
    addPlaceInStack();
    emit("sw $fp, ($sp)");
    addPlaceInStack();
    emit("sw $ra, ($sp)");

    return first_command;
    //after this the arguments should be put in the stack
}

int updateSPBeforeCall(std::string func_name, SymTable &table) {
    emitComment("update $sp according to the symbol table");
    return emit("add $sp, $fp, (-" + numToString(table.nextOffset()) + ")");
}

int emitSaveRegisters() {
    int first_command = INT_MAX;
    for (int i = 0; i < NUM_OF_REGISTERS; ++i) {
        first_command = std::min(first_command, emitPushReg(i));
    }

    return first_command;
}

int emitPushReg(int reg_num) {
    int first_command = addPlaceInStack();
    emit("sw " + regName(reg_num) + ", ($sp)");
    return first_command;
}

int emitLoadRegisters() {
    int first_command = INT_MAX;
    for (int i = NUM_OF_REGISTERS - 1; i >= 0; --i) {
        first_command = std::min(first_command, emitPopReg(i));
    }

    return first_command;
}

int emitPopReg(int reg_num) {
    int first_command = emit("lw " + regName(reg_num) + ", ($sp)");
    removePlaceInStack();
    return first_command;
}

int emitLoadVar(int reg_num, int offset) {
    offset *= 4;
    return emit("lw " + regName(reg_num) + ", " + numToString(-offset) + "($fp)");
}

int emitSaveVar(int reg_num, int offset) {
    offset *= 4;
    int first_command = emit("add " + regName(reg_num) + ", $fp, " + numToString(-offset));
    emit("sw " + regName(reg_num) + ", " + "(" + regName(reg_num) + ")");
    return first_command;
}

int emitLoadVar(int reg_num, std::string &ID, SymTable &table) {
    emitComment("load the variable " + ID + "into the register " + regName(reg_num));
    return emitLoadVar(reg_num, table.getSymbolEntry(ID).offset);
}

int emitSaveVar(int reg_num, std::string &ID, SymTable &table) {
    emitComment("save the variable " + ID + "from the register " + regName(reg_num) + "into the stack");
    return emitSaveVar(reg_num, table.getSymbolEntry(ID).offset);
}

int emitLoadStructField(int reg_num, std::string &struct_name, std::string &field_name, SymTable &table, StructType &t) {
    emitComment("Load the value of the field " + struct_name + "." + field_name + "into " + regName(reg_num));
    return emitLoadStructField(reg_num, table.getSymbolEntry(struct_name).offset, field_name, table, t);
}

int emitSaveStructField(int reg_num, std::string &struct_name, std::string &field_name, SymTable &table, StructType &t) {
    emitComment("Save the value of the field " + struct_name + "." + field_name + "from " + regName(reg_num));
    return emitSaveStructField(reg_num, table.getSymbolEntry(struct_name).offset, field_name, table, t);
}

int emitLoadStructField(int reg_num, int offset, std::string &field_name, SymTable &table, StructType &t){
    return emitSaveVar(reg_num, offset + t.fieldOffset(field_name));
}

int emitSaveStructField(int reg_num, int offset, std::string &field_name, SymTable &table, StructType &t){
    return emitLoadVar(reg_num, offset + t.fieldOffset(field_name));
}

int emitStructsEq(int offset1, int offset2, StructType& t, regHandler& r){
    int reg = r.getAvailableRegister();
    int first_command = INT_MAX;
    for(int i=0; i < t.fields.size(); ++i){
        first_command = std::min(first_command, emitSaveVar(reg, i + offset2));
        emitLoadVar(reg, i + offset1);
    }

    return first_command;
}

int emitStructsEq(std::string& struct1, std::string& struct2, SymTable& table, StructType& t, regHandler& r){
    emitComment("executing " + struct1 + " = " + struct2);
    return emitStructsEq(table.getSymbolEntry(struct1).offset, table.getSymbolEntry(struct2).offset, t, r);
}

int emitFuncCall(std::string func_name, SymTable& table, std::vector<std::vector<StructType> > &structs_stack){
    //move frame pointer to new location
    int first_command = emit("move $fp, $sp");
    //add place in stack so that the usage of the symbol table's offsets will be correct
    addPlaceInStack();
    //call func
    emit("jal " + func_name);
    //remove all func arguments from the stack
    removePlaceInStack(funcArgsTotOffset(table.getSymbolEntry(func_name).func_type.first, table, structs_stack) + 1);

    //pop $ra and $fp
    emit("lw $ra, ($sp)");
    removePlaceInStack();
    emit("lw $fp, ($sp)");
    removePlaceInStack();

    //load all registers
    emitLoadRegisters();

    return first_command;
}

int emitReturn(int reg_num){
    int first_command = INT_MAX;
    emitComment("return from function");
    if(reg_num != -1){
        first_command = emit("move $v0, " + regName(reg_num));
    }
    first_command = std::min(first_command, emit("jr $ra"));
    return first_command;
}