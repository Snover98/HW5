//
// Created by user on 16/01/2019.
//

#ifndef HW5_COMPARISON_OPERATORS_H
#define HW5_COMPARISON_OPERATORS_H

#include "Node.h"
#include <string>
#include "register_handler.h"


std::string relopCommand(std::string& op);
std::string relopString(Expression* exp1, Expression* exp2, std::string& op);

#endif //HW5_COMPARISON_OPERATORS_H
