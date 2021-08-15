//
// Created by Kosuke Futamata on 16/08/2021.
//

#include "Instruction.h"
#include <string>

Instruction::Instruction(InstructionType type, int line_number, const std::string& dest="",
                         const std::string &comp="", const std::string &jump="", const std::string &symbol="")
        : type(type), line_number(line_number), dest(dest), comp(comp), jump(jump), symbol(symbol)
{
}
