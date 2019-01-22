//
// Created by user on 16/01/2019.
//

#include "comparison_operators.h"

std::string relopCommand(std::string &op) {
    if (op == "==") {
        return "beq";
    } else if (op == "!=") {
        return "bne";
    } else if (op == "<") {
        return "blt";
    } else if (op == ">") {
        return "bgt";
    } else if (op == "<=") {
        return "ble";
    } else if (op == ">=") {
        return "bge";
    }

    return "nop";
}


std::string relopString(Expression *exp1, Expression *exp2, std::string &op) {
    //create the string of the command that will compute the expression
    return relopCommand(op) + " " + regName(exp1->used_register) + ", " + regName(exp2->used_register) + ", ";
}