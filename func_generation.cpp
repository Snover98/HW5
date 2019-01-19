//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#include "func_generation.h"


int emitFuncStart(std::string &func_name) {
    emitComment("CODE OF FUNCTION " + func_name);
    return emit(func_name + ":");
}

int emitSetupFuncCall(std::string &func_name, SymTable &table) {
    //make sure that $sp is correct
    updateSPBeforeCall(func_name, table);
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

int updateSPBeforeCall(std::string &func_name, SymTable &table) {
    emitComment("update $sp according to the symbol table");
    return emit("add $sp, $fp, (-" + numToString(table.nextOffset()) + ")");
}

int emitSaveRegisters() {
    int last_command = -1;
    for (int i = 0; i < NUM_OF_REGISTERS; ++i) {
        last_command = emitPushReg(i);
    }

    return last_command;
}

int emitPushReg(int reg_num) {
    addPlaceInStack();
    return emit("sw " + regName(reg_num) + ", ($sp)");
}

int emitLoadRegisters() {
    int last_command = -1;
    for (int i = NUM_OF_REGISTERS - 1; i >= 0; --i) {
        last_command = emitPopReg(i);
    }

    return last_command;
}

int emitPopReg(int reg_num) {
    emit("lw " + regName(reg_num) + ", ($sp)");
    return removePlaceInStack();
}

int emitLoadVar(int reg_num, int offset) {
    offset *= 4;
    return emit("lw " + regName(reg_num) + ", " + numToString(-offset) + "($fp)");
}

int emitSaveVar(int reg_num, int offset) {
    offset *= 4;
    emit("add " + regName(reg_num) + ", $fp, " + numToString(-offset));
    return emit("sw " + regName(reg_num) + ", " + "(" + regName(reg_num) + ")");
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
    int last_command = -1;
    for(int i=0; i < t.fields.size(); ++i){
        emitSaveVar(reg, i + offset2);
        last_command = emitLoadVar(reg, i + offset1);
    }

    return last_command;
}

int emitStructsEq(std::string& struct1, std::string& struct2, SymTable& table, StructType& t, regHandler& r){
    emitComment("executing " + struct1 + " = " + struct2);
    return emitStructsEq(table.getSymbolEntry(struct1).offset, table.getSymbolEntry(struct2).offset, t, r);
}

int emitFuncCall(std::string func_name, SymTable& table, std::vector<std::vector<StructType> > &structs_stack){
    //move frame pointer to new location
    emit("move $fp, $sp");
    //call func
    emit("jal " + func_name);
    //remove all func arguments from the stack
    removePlaceInStack(funcArgsTotOffset(table.getSymbolEntry(func_name).func_type.first, table, structs_stack));

    //pop $ra and $fp
    emit("lw $ra, ($sp)");
    removePlaceInStack();
    emit("lw $fp, ($sp)");
    removePlaceInStack();

    //load all registers
    return emitLoadRegisters();
}

int emitReturn(int reg_num){
    emitComment("return from function");
    if(reg_num != -1){
        emit("move $v0, " + regName(reg_num));
    }
    return emit("jr $ra");
}