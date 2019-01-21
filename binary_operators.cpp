//
// Created by Assaf-Haik-Barouch on 14/01/2019.
//
#include <sstream>
#include "binary_operators.h"

std::string operatorCommand(std::string &op) {
    if (op == "+") {
        return "addu";
    } else if (op == "/") {
        return "divu";
    } else if (op == "*") {
        return "mulou";
    } else if (op == "-") {
        return "subu";
    }

    return "nop";
}


std::string operatorString(Expression *exp1, Expression *exp2, std::string &op, regHandler &r) {
    //create the string of the command that will compute the expression
    std::stringstream command;
    //the new expression will be in the same register as exp1's current one
    command << operatorCommand(op) << " " << regName(exp1->used_register) << ", ";
    command << regName(exp1->used_register) << ", " << regName(exp2->used_register);
    //free the register used by exp2
    r.freeRegister(exp2->used_register);

    return command.str();
}

std::string truncByte(Expression* exp){
    //create the string of the command that will truncuate the byte
    std::stringstream command;
    command << "and " << regName(exp->used_register) << ", " << regName(exp->used_register) << ", " << "255";

    return command.str();
}