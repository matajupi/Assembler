//
// Created by Kosuke Futamata on 16/08/2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H


#include <string>
#include <vector>
#include "Parser.h"
#include "CodeGenerator.h"


class Assembler {
private:
    std::vector<std::string> source;
    static bool create_symbol_table(std::map<std::string, int>&, std::vector<Instruction>&, std::vector<AssembleError>&);
public:
    explicit Assembler(std::vector<std::string>&);
    bool assemble(std::vector<std::string>&, std::vector<AssembleError>&);
};


#endif //ASSEMBLER_ASSEMBLER_H
