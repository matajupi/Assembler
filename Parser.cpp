//
// Created by Kosuke Futamata on 16/08/2021.
//

#include "Parser.h"

Parser::Parser(std::vector<std::string> &source) : source(source)
{
}

bool Parser::parse(std::vector<Instruction> &instructions, std::vector<AssembleError> &errors)
{
    for (auto i = 0; source.size() > i; i++)
    {
        auto line = source.at(i);

        std::string dest, comp, jump, symbol;
        InstructionType type;
        std::smatch match;

        if (std::regex_match(line, match, A_COMMAND_PATTERN()))
        {
            symbol = match[1].str();
            type = InstructionType::A_COMMAND;
        }
        else if (std::regex_match(line, match, L_COMMAND_PATTERN()))
        {
            symbol = match[1].str();
            type = InstructionType::L_COMMAND;
        }
        else if (std::regex_match(line, match, C_COMMAND_PATTERN()))
        {
            dest = match[1].str();
            comp = match[2].str();
            jump = match[3].str();
            type = InstructionType::C_COMMAND;
        }
        else
        {
            auto error = AssembleError("Invalid syntax.", i + 1);
            errors.push_back(error);
            continue;
        }

        Instruction instruction(type, i + 1, dest, comp, jump, symbol);
        instructions.push_back(instruction);
    }
    return errors.empty();
}

std::regex Parser::A_COMMAND_PATTERN() {
    return std::regex(R"(@([0-9]+|[a-zA-Z_:\.\$][0-9a-zA-Z_:\.\$]*))");
}

std::regex Parser::C_COMMAND_PATTERN() {
    return std::regex(R"((?:(A?M?D?)=)?([^;]+)(?:;(.+))?)");
}

std::regex Parser::L_COMMAND_PATTERN() {
    return std::regex(R"(\([a-zA-Z_:\.\$][0-9a-zA-Z_:\.\$]*\))");
}
