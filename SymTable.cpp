//
// Created by Assaf-Haik-Barouch on 10/12/2018.
//

#include "SymTable.h"

#define CALCOFFSET() scope_entries.empty() ? table_offset : scope_entries.back().offset + typeOffset(scope_entries.back())

int SymTable::typeOffset(SymEntry& entry) {
    int offset = 0;

    switch (entry.type) {
        case STRUCTTYPE:
            offset += structTypeOffset(entry.struct_type) - 1;
        default:
            offset++;
        case FUNCTYPE:;
    }

    return offset;
}

SymEntry SymTable::getSymbolEntry(const std::string &ID) {
    //find the entry with the same ID in this table
    for (std::vector<SymEntry>::iterator it = scope_entries.begin(); it != scope_entries.end(); ++it) {
        if (ID == (*it).ID) {
            return (*it);
        }
    }

    //if there is non return an entry with type of NOTYPE
    return SymEntry();
}


VarType SymTable::getSymType(const std::string &ID) {
    return getSymbolEntry(ID).type;
}

bool SymTable::isSymInTable(const std::string &ID) {
    return (getSymbolEntry(ID).type != NOTYPE);
}

FunctionType SymTable::getFunctionType(const std::string &ID) {
    return getSymbolEntry(ID).func_type;
}

std::string SymTable::getStructType(const std::string &ID) {
    return getSymbolEntry(ID).struct_type;
}

void SymTable::addEntry(SymEntry e) {
    if (isSymInTable(e.ID)) {
        throw ShadowingException(e.ID);
    }

    scope_entries.push_back(e);
}

void SymTable::addEntry(const std::string &ID, const std::string &struct_type) {
    addEntry(SymEntry(ID, struct_type, CALCOFFSET()));
}

void SymTable::addEntry(const std::string &ID, VarType type) {
    addEntry(SymEntry(ID, type, CALCOFFSET()));
}

void SymTable::addEntry(const std::string &ID, const std::vector<FuncParam> &func_params, VarType ret_type) {
    addEntry(SymEntry(ID, func_params, ret_type));
}

int SymTable::structTypeOffset(const std::string &ID) {
    return getStructTypeEntry(*structs_stack, ID).fields.size();
}

int SymTable::nextOffset(){
    return CALCOFFSET();
}

SymEntry getSymbolEntry(const std::string &ID, std::vector<SymTable>& tables_stack){
    //find the entry with the same ID in each scope
    for (std::vector<SymTable>::iterator it = tables_stack.begin(); it != tables_stack.end(); ++it) {
        SymEntry res = (*it).getSymbolEntry(ID);
        if (ID == res.ID) {
            return res;
        }
    }

    return SymEntry();
}

bool isSymInTable(const std::string &ID, std::vector<SymTable>& tables_stack){
    return (getSymbolEntry(ID, tables_stack).type != NOTYPE);
}

VarType getSymType(const std::string &ID, std::vector<SymTable>& tables_stack){
    return getSymbolEntry(ID, tables_stack).type;
}

FunctionType getFunctionType(const std::string &ID, std::vector<SymTable>& tables_stack){
    return getSymbolEntry(ID, tables_stack).func_type;
}

std::string getStructType(const std::string &ID, std::vector<SymTable>& tables_stack){
    return getSymbolEntry(ID, tables_stack).struct_type;
}
