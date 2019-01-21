//
// Created by Assaf-Haik-Barouch on 14/01/2019.
//

#ifndef HW5_REGISTER_HANDLER_H
#define HW5_REGISTER_HANDLER_H

#include <vector>
#include <string>

#define NUM_OF_REGISTERS 18


class regHandler {
    std::vector<bool> available_registers;

public:
    regHandler(): available_registers(std::vector<bool>(NUM_OF_REGISTERS)){}

    //returns the smallest register available
    int getAvailableRegister();
    //frees register num i
    void freeRegister(int i);
    //tells you if a register is taken
    bool isFree(int i);
};

//return register name
std::string regName(int i);


#endif //HW5_REGISTER_HANDLER_H
