//
// Created by Assaf-Haik-Barouch on 12/12/2018.
//

#ifndef HW3_STRUCTTYPE_H
#define HW3_STRUCTTYPE_H

#include <vector>
#include <string>
#include "Exceptions.h"

enum VarType {
    INTTYPE, BYTETYPE, BOOLTYPE, STRUCTTYPE, FUNCTYPE, STRINGTYPE, NOTYPE
};

typedef std::vector<std::pair<std::string, VarType> > StructFieldsType;

struct StructType {
    std::string type_name;
    StructFieldsType fields;

    StructType() : type_name(std::string("")), fields(StructFieldsType()) {}

//    StructType(StructType &t) : type_name(std::string(t.type_name)), fields(t.fields) {}

    StructType(const std::string& name, const StructFieldsType& fields) : type_name(name), fields(fields) {}

    VarType getFieldType(const std::string& field_name);

    StructType& operator=(const StructType& t){
        type_name = t.type_name;
        fields = StructFieldsType(fields);
        return *this;
    }
};

void addStructType(std::vector<StructType> &structs, StructType t);

void addStructType(std::vector<StructType> &structs, const std::string &ID,
                   const std::vector<std::pair<std::string, VarType> > &fields);

bool isStructTypeInTable(const std::vector<StructType> &structs, const std::string &ID);

bool isStructTypeInTable(const std::vector<std::vector<StructType> > &structs_stack, const std::string &ID);

StructType getStructTypeEntry(const std::vector<StructType> &structs, const std::string &ID);

StructType getStructTypeEntry(const std::vector<std::vector<StructType> > &structs_stack, const std::string &ID);


#endif //HW3_STRUCTTYPE_H
