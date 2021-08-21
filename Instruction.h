//
// Created by Kosuke Futamata on 21/08/2021.
//

#ifndef ASSEMBLER_INSTRUCTION_H
#define ASSEMBLER_INSTRUCTION_H

#include <string>
#include "assembler_all.h"


enum InstructionKind
{
    A_COMMAND,
    C_COMMAND,
    L_COMMAND,
};

class Instruction
{
public:
    InstructionKind kind;
    bool is_numeric;
    std::string symbol;
    std::string dest;
    std::string comp;
    std::string jump;
};

#endif // ASSEMBLER_INSTRUCTION_H
