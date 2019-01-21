//
// Created by Assaf-Haik-Barouch on 14/01/2019.
//

#include "register_handler.h"
#include <istream>
#include <iostream>
#include <sstream>

int regHandler::getAvailableRegister() {
    for (int i = 0; i < NUM_OF_REGISTERS; i++) {
        if (!available_registers[i]) {
            available_registers[i] = true;
            return i;
        }
    }
    //note: not suppose to get here
    return -1;
}

void regHandler::freeRegister(int i) {
    if (i < 0 || i >= NUM_OF_REGISTERS) {
        //note: not suppose to get here
        std::cout << "ERROR" << std::endl;
        return;
    }
    available_registers[i] = false;
}

std::string regName(int i){
    std::stringstream s;
    s << '$' << i+8;
    return s.str();
}

bool regHandler::isFree(int i){
    return available_registers[i];
}