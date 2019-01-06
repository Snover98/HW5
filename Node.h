//
// Created by Assaf-Haik-Barouch on 13/12/2018.
//

#ifndef HW3_NODE_H
#define HW3_NODE_H

#include <string>
#include <vector>
#include "StructType.h"


//the type of the expression
enum ExpType {
    INTEXP, BYTEEXP, BOOLEXP, STRUCTEXP, FUNCEXP, STRINGEXP, VOIDEXP
};

//general type for lex output
struct Node {

};

//struct for expressions, we need to know their type
struct Expression : public Node {
    ExpType exp_type;

    Expression(const ExpType exp_type) : Node(), exp_type(exp_type) {}
};

//struct for structures, the extra string field is so we can now what kind of struct it is
struct Structure : public Expression {
    std::string struct_type;

    Structure(const ExpType exp_type) : Expression(exp_type), struct_type(std::string("")){}
    Structure(const std::string &struct_type) : Expression(STRUCTEXP), struct_type(std::string(struct_type)) {}
};

//used when there is an identifier read by lex, only used to create the relevant Expression and than deleted
struct Identifier : public Node {
    std::string ID;

    Identifier(const std::string &ID) : Node(), ID(std::string(ID)) {}
};

struct ExpressionList : public Node {
    std::vector<Structure> expressions;

    ExpressionList() : Node(), expressions(std::vector<Structure>()) {}
};

struct StructMemory : public Node {
    std::pair<std::string, VarType> field;
    int line;

    StructMemory(const std::string &ID, VarType type, int line) : field(std::pair<std::string, VarType>(std::string(ID), type)), line(line) {}
};

struct StructMemList : public Node {
    StructFieldsType fields;

    StructMemList() : Node(), fields(StructFieldsType()) {}

    int fieldLocation(std::string &field_name){
        int i = 1;
        for (StructFieldsType::const_iterator it = fields.begin(); it != fields.end(); ++it) {
            if (field_name == (*it).first) return i;
            ++i;
        }

        return 0;
    }

    bool isFieldNameTaken(std::string &field_name) {
        return (fieldLocation(field_name) > 0);
    }
};

struct Formal : public Node {
    std::string ID;
    ExpType type;

    Formal(const std::string &ID, ExpType type) : Node(), ID(std::string(ID)), type(type) {}
};

struct FormalStruct : public Formal {
    std::string struct_type;

    FormalStruct(const std::string &ID, const std::string &struct_type, ExpType type = STRUCTEXP) : Formal(ID, type),
                                                                                                    struct_type(
                                                                                                            std::string(
                                                                                                                    struct_type)) {}

    FormalStruct(const std::string &ID, ExpType type) : Formal(ID, type), struct_type(std::string("")) {}

};

struct FormalsList : public Node {
    std::vector<FormalStruct> formals;

    FormalsList() : Node(), formals(std::vector<FormalStruct>()) {}

    bool isParamNameTaken(const std::string &param_name) {
        //look for a field with the inputted name
        for (std::vector<FormalStruct>::const_iterator it = formals.begin(); it != formals.end(); ++it) {
            if (param_name == (*it).ID) return true;
        }

        //if now field with that name was found, the name is not taken
        return false;
    }
};


//checks if an expression is a number
inline bool isNumExp(Expression *e) {
    return (e->exp_type == INTEXP || e->exp_type == BYTEEXP);
}

//returns the type of a binary operator between nums (like +,-,/,*)
inline ExpType operatorType(Expression *num1, Expression *num2) {
    return ((num1->exp_type == INTEXP || num2->exp_type == INTEXP) ? INTEXP : BYTEEXP);
}

bool isLegalExpType(Expression *actual, Expression *expected);
bool isLegalExpType(Expression *actual, ExpType expected);
bool isLegalExpType(Expression *actual, std::string &expected);
bool isLegalExpType(ExpType actual, ExpType expected);
bool isLegalExpType(std::string &actual, std::string &expected);

Structure expressionToList(Expression *e);


#endif //HW3_NODE_H
