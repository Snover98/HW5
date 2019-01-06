//
// Created by Assaf-Haik-Barouch on 19/12/2018.
//
#include "Node.h"

bool isLegalExpType(Expression *actual, Expression *expected) {
    if (expected->exp_type == INTEXP) {
        return (actual->exp_type == INTEXP || actual->exp_type == BYTEEXP);
    }

    if (expected->exp_type == STRUCTEXP && actual->exp_type == STRUCTEXP) {
        return (((Structure *) actual)->struct_type == ((Structure *) expected)->struct_type);
    }

    return (expected->exp_type == actual->exp_type);
}

bool isLegalExpType(Expression *actual, ExpType expected) {
    Expression e = Expression(expected);
    return isLegalExpType(actual, &e);
}

bool isLegalExpType(Expression *actual, std::string &expected) {
    Structure s = Structure(expected);
    return isLegalExpType(actual, &s);
}

bool isLegalExpType(ExpType actual, ExpType expected) {
    Expression e = Expression(actual);
    return isLegalExpType(&e, expected);
}

bool isLegalExpType(std::string &actual, std::string &expected) {
    Structure s = Structure(actual);
    return isLegalExpType(&s, expected);
}

Structure expressionToList(Expression *e){
    if(e->exp_type == STRUCTEXP){
        return *((Structure*)e);
    }

    return Structure(e->exp_type);
}