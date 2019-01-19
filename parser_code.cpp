//
// Created by Assaf-Haik-Barouch on 19/01/2019.
//

#include "parser_code.h"

void addPrints(){
    std::vector<FuncParam> print_func_params = std::vector<FuncParam>();
    std::vector<FuncParam> printi_func_params = std::vector<FuncParam>();

    print_func_params.push_back(FuncParam(STRINGTYPE));
    printi_func_params.push_back(FuncParam(INTTYPE));

    tables_stack.back().addEntry("print", print_func_params, NOTYPE);
    //emit code for print
    emitFuncStart("print");
    emit("lw $a0,0($sp)");
    emit("li $v0,4");
    emit("syscall");
    emit("jr $ra");
    emitFuncEnd("print");

    tables_stack.back().addEntry("printi", printi_func_params, NOTYPE);
    //emit code for printi
    emitFuncStart("printi");
    emit("lw $a0,0($sp)");
    emit("li $v0,1");
    emit("syscall");
    emit("jr $ra");
    emitFuncEnd("printi");
}

void popScope(){
    std::vector<SymEntry> scope_entries = tables_stack.back().scope_entries;

    output::endScope();

    for(std::vector<SymEntry>::iterator it = scope_entries.begin(); it != scope_entries.end(); ++it){
        std::string type;

        if((*it).type == FUNCTYPE){
            type = funcToString((*it).func_type);
        } else{
            type = typeToString((*it).type) + (((*it).type == STRUCTTYPE) ? (" " + (*it).struct_type) : "");
        }

        output::printID((*it).ID, (*it).offset, type);
    }

    std::vector<StructType> scope_structs = structs_stack.back();

    for(std::vector<StructType>::iterator it = scope_structs.begin(); it != scope_structs.end(); ++it){
        vector<std::string> memTypes = vector<std::string>();
        vector<std::string> memNames = vector<std::string>();

        for(StructFieldsType::const_iterator field_it = (*it).fields.begin(); field_it != (*it).fields.end(); ++field_it){
            memTypes.push_back(typeToString((*field_it).second));
            memNames.push_back((*field_it).first);
        }

        output::printStructType((*it).type_name, memTypes, memNames);
    }

    tables_stack.pop_back();
    structs_stack.pop_back();
}

std::string funcToString(FunctionType &func_type){
    std::string t = typeToString(func_type.second);
    std::vector<std::string> func_args = funcArgTypes(func_type);
    return output::makeFunctionType(t, func_args);
}

std::vector<std::string> funcArgTypes(FunctionType &func_type){
    std::vector<std::string> argTypes = vector<std::string>();

    for(std::vector<FuncParam>::iterator it = func_type.first.begin(); it != func_type.first.end(); ++it){
        argTypes.push_back(typeToString((*it).type) + (((*it).type == STRUCTTYPE) ? (" " + (*it).struct_type) : ""));
    }

    return argTypes;
}

std::string typeToString(VarType type){
    switch(type){
        case INTTYPE:
            return "INT";
        case BYTETYPE:
            return "BYTE";
        case BOOLTYPE:
            return "BOOL";
        case STRUCTTYPE:
            return "struct";
        case STRINGTYPE:
            return "STRING";
        default:
            return "VOID";
    }
}

void addFuncScope(const std::string &ID, const std::vector<FormalStruct> &formals, ExpType ret_type){
    cur_ret_type = ret_type;

    std::vector<FuncParam> func_params = std::vector<FuncParam>();

    for(std::vector<FormalStruct>::const_iterator it = formals.begin(); it!=formals.end(); ++it){
        if((*it).type == STRUCTEXP){
            func_params.push_back(FuncParam((*it).struct_type));
        } else {
            func_params.push_back(FuncParam(expToVar((*it).type)));
        }
    }

    tables_stack.back().addEntry(ID, func_params, expToVar(ret_type));

    addEmptyScope();

    int offset = 0;
    for(std::vector<FormalStruct>::const_iterator it = formals.begin(); it!=formals.end(); ++it){
        SymEntry* e;

        if((*it).type == STRUCTEXP){
            offset -= tables_stack.back().structTypeOffset((*it).struct_type);
            e = new SymEntry((*it).ID, (*it).struct_type, offset);
        } else {
            e = new SymEntry((*it).ID, expToVar((*it).type), --offset);
        }

        tables_stack.back().addEntry(*e);
        delete e;
    }

    emitFuncStart(ID);
    //add empty place for local variables
}

void addEmptyScope(){
    SymTable t = SymTable(&structs_stack, tables_stack.back().nextOffset());
    tables_stack.push_back(t);
    structs_stack.push_back(std::vector<StructType>());
}

VarType expToVar(ExpType e){
    switch(e){
        case INTEXP:
            return INTTYPE;
        case BYTEEXP:
            return BYTETYPE;
        case BOOLEXP:
            return BOOLTYPE;
        case STRUCTEXP:
            return STRUCTTYPE;
        case FUNCEXP:
            return FUNCTYPE;
        case STRINGEXP:
            return STRINGTYPE;
        default:
            //note that no entry in the symbol table can be string or void!
            return NOTYPE;
    }
}

ExpType varToExp(VarType t){
    switch(t){
        case INTTYPE:
            return INTEXP;
        case BYTETYPE:
            return BYTEEXP;
        case BOOLTYPE:
            return BOOLEXP;
        case STRUCTTYPE:
            return STRUCTEXP;
        case FUNCTYPE:
            return FUNCEXP;
        case STRINGTYPE:
            return STRINGEXP;
        default:
            //note that no entry in the symbol table can be string or void!
            return VOIDEXP;
    }
}