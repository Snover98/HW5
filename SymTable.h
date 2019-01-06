//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#ifndef HW3_SYMTABLE_H
#define HW3_SYMTABLE_H

#include <string>
#include <vector>
#include "Exceptions.h"
#include "StructType.h"

struct FuncParam {
    VarType type;
    std::string struct_type;

    FuncParam(VarType type) : type(type), struct_type(std::string("")) {}

    FuncParam(const std::string &struct_type) : type(STRUCTTYPE), struct_type(std::string(struct_type)) {}

};

typedef std::pair<std::vector<FuncParam>, VarType> FunctionType;

struct SymEntry {
    std::string ID;
    VarType type;
    int offset;
    FunctionType func_type;
    std::string struct_type;

    SymEntry() : type(NOTYPE), offset(0) {}

    SymEntry(const std::string &ID, const std::string &struct_type, int offset) : ID(std::string(ID)), type(STRUCTTYPE),
                                                                                  offset(offset),
                                                                                  struct_type(
                                                                                          std::string(struct_type)) {}

    SymEntry(const std::string &ID, VarType type, int offset) : ID(std::string(ID)), type(type), offset(offset),
                                                                struct_type("") {}

    SymEntry(const std::string &ID, const std::vector<FuncParam> &func_params, VarType ret_type) : ID(std::string(ID)),
                                                                                                   struct_type(""),
                                                                                                   type(FUNCTYPE),
                                                                                                   offset(0),
                                                                                                   func_type(
                                                                                                           FunctionType(
                                                                                                                   func_params,
                                                                                                                   ret_type)) {}

    bool isVariable() {
        return (type == BOOLTYPE || type == BYTETYPE || type == INTTYPE || type == STRUCTTYPE);
    }
};

class SymTable {
private:
    int table_offset;
    std::vector<std::vector<StructType> > *structs_stack;


    int typeOffset(SymEntry& entry);


public:
    std::vector<SymEntry> scope_entries;

    SymTable(std::vector<std::vector<StructType> > *structs_stack, int offset = 0)
            : table_offset(offset),
              scope_entries(std::vector<SymEntry>()),
              structs_stack(structs_stack) {}

    void addEntry(SymEntry e);

    void addEntry(const std::string &ID, const std::string &struct_type);

    void addEntry(const std::string &ID, VarType type);

    void addEntry(const std::string &ID, const std::vector<FuncParam> &func_params, VarType ret_type);

    SymEntry getSymbolEntry(const std::string &ID);

    bool isSymInTable(const std::string &ID);

    VarType getSymType(const std::string &ID);

    FunctionType getFunctionType(const std::string &ID);

    std::string getStructType(const std::string &ID);

    int structTypeOffset(const std::string &ID);

    int nextOffset();
};

SymEntry getSymbolEntry(const std::string &ID, std::vector<SymTable>& tables_stack);

bool isSymInTable(const std::string &ID, std::vector<SymTable>& tables_stack);

VarType getSymType(const std::string &ID, std::vector<SymTable>& tables_stack);

FunctionType getFunctionType(const std::string &ID, std::vector<SymTable>& tables_stack);

std::string getStructType(const std::string &ID, std::vector<SymTable>& tables_stack);


#endif //HW3_SYMTABLE_H
