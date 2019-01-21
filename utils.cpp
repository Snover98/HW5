//
// Created by Assaf-Haik-Barouch on 18/01/2019.
//

#include "utils.h"

//converting int to string - found online
std::string numToString(int num) {
    std::stringstream str1;
    str1 << num;
    std::string num_as_string = str1.str();
    return num_as_string;
}

int emitComment(std::string comment) {
    return emit("#" + comment);
}

int emitComment(std::stringstream &comment) {
    return emitComment(comment.str());
}

int emit(std::string str) {
    return CodeBuffer::instance().emit(str);
}

int emit(std::stringstream &str) {
    return emit(str.str());
}

int addPlaceInStack(int offset) {
    //convert offset to bytes
    offset *= 4;
    return emit("add $sp, $sp, (-" + numToString(offset) + ")");
}

int removePlaceInStack(int offset) {
    //convert offset to bytes
    offset *= 4;
    return emit("add $sp, $sp, (" + numToString(offset) + ")");
}

int funcArgsTotOffset(std::vector<FuncParam> params, SymTable &table,
                      std::vector<std::vector<StructType> > &structs_stack) {
    int offset = 0;
    for(std::vector<FuncParam>::iterator it = params.begin(); it != params.end(); ++it){
        if((*it).type != STRUCTTYPE){
            ++offset;
        } else {
            offset += getStructTypeEntry(structs_stack, (*it).struct_type).fields.size();
        }
    }
    return offset;
}

int emitTerminate(){
    int first_command = emit("li $v0, 10");
    emit("syscall");
    return first_command;
}

std::string strData(std::string str){
    //if the string already exists, return the label
    if(string_labels.count(str) > 0){
        return string_labels[str];
    }

    std::string str_label = "str_" + numToString(++num_strings);
    CodeBuffer::instance().emitData(str_label + ":");
    CodeBuffer::instance().emitData(".asciiz \"" + str +"\"");

    string_labels[str] = str_label;

    return str_label;
}

int emitDivByZeroCheck(int reg, std::string& handler_label){
    return emit("beq " + regName(reg) + ", 0 ," + handler_label);
}

std::string emitDivByZeroHandler(){
    std::string handler_label = CodeBuffer::instance().genLabel();
    std::string error_msg = strData("Error division by zero \n");
    //load error message as an argument for the syscall
    emit("la $a0, " + error_msg);
    //prime syscall
    emit("li $v0, 4");
    //print the error message
    emit("syscall");
    //terminate the program
    emitTerminate();

    return handler_label;
}