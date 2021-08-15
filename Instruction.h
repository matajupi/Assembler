//
// Created by Kosuke Futamata on 16/08/2021.
//

#ifndef ASSEMBLER_INSTRUCTION_H
#define ASSEMBLER_INSTRUCTION_H


#include <string>
#include <utility>


enum InstructionType {
    A_COMMAND,
    C_COMMAND,
    L_COMMAND,
};


class Instruction {
public:
    const InstructionType type;
    const int line_number;
    const std::string &dest;
    const std::string &comp;
    const std::string &jump;
    const std::string &symbol;

    explicit Instruction(InstructionType type, int line_number, const std::string &dest,
                         const std::string &comp, const std::string &jump, const std::string &symbol);
};


#endif //ASSEMBLER_INSTRUCTION_H
