//
// Created by Kosuke Futamata on 16/08/2021.
//

#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H


#include <string>
#include <vector>
#include <regex>
#include "Instruction.h"
#include "AssembleError.h"


class Parser {
private:
    static std::regex A_COMMAND_PATTERN();
    static std::regex C_COMMAND_PATTERN();
    static std::regex L_COMMAND_PATTERN();
    static std::regex COMMENT_PATTERN();
    std::vector<std::string> source;
public:
    explicit Parser(std::vector<std::string>&);
    bool parse(std::vector<Instruction>&, std::vector<AssembleError>&);
};


#endif //ASSEMBLER_PARSER_H
