//
// Created by Assaf-Haik-Barouch on 14/01/2019.
//

#ifndef HW5_BINARY_OPERATORS_H
#define HW5_BINARY_OPERATORS_H

#include "Node.h"
#include <string>
#include "register_handler.h"


std::string operatorCommand(std::string& op);
std::string operatorString(Expression* exp1, Expression* exp2, std::string& op, regHandler& r);
std::string truncByte(Expression* exp);


#endif //HW5_BINARY_OPERATORS_H
