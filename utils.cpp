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
    emit("li $v0, 10");
    return emit("syscall");
}

std::string genStrData(std::string str){
    //if the string already exists, return the label
    std::map<std::string, std::string>::iterator it = string_labels.find(str);
    if(it != string_labels.end()){
        return (*it).second;
    }

    std::string str_label = "str_" + numToString(++num_strings);
    CodeBuffer::instance().emitData(str_label + ":");
    CodeBuffer::instance().emitData(".ascii "+str);

    string_labels[str] = str_label;

    return str_label;
}