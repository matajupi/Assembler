//
// Created by Kosuke Futamata on 16/08/2021.
//

#include "CodeGenerator.h"
#include <bitset>
#include <sstream>

CodeGenerator::CodeGenerator(std::vector<Instruction> &instructions, std::map<std::string, int> &symbol_table)
    : instructions(instructions), symbol_table(symbol_table)
{
}

bool CodeGenerator::generate(std::vector<std::string> &code, std::vector<AssembleError> &errors)
{
    for (auto instruction : instructions)
    {
        std::string line;
        if (instruction.type == InstructionType::A_COMMAND)
        {
            auto symbol = instruction.symbol;
            if (symbol_table.contains(symbol))
            {
                std::stringstream ss;
                ss << std::bitset<15>(symbol_table[symbol]);
                line = "0" + ss.str();
            }
            else
            {
                std::stringstream ss;
                ss << std::bitset<15>(std::stoi(symbol));
                line = "0" + ss.str();
            }
        }
        else if (instruction.type == InstructionType::C_COMMAND)
        {
            auto dest = instruction.dest;
            auto comp = instruction.comp;
            auto jump = instruction.jump;

            std::string dest_bin, comp_bin, jump_bin;

            if (dest.empty())
                dest_bin = dest_table.at("null");
            else if (dest_table.contains(dest))
                dest_bin = dest_table.at(dest);
            else
            {
                auto error = AssembleError("A 'destination' part named '" + dest + "' is not defined.", instruction.line_number);
                errors.push_back(error);
                dest_bin = dest_table.at("null");
            }

            if (comp_table.contains(comp))
                comp_bin = comp_table.at(comp);
            else if (comp.empty())
            {
                auto error = AssembleError("A instruction requires 'compute' part.", instruction.line_number);
                errors.push_back(error);
                comp_bin = comp_table.at("0");
            }
            else
            {
                auto error = AssembleError("A 'compute' part named '" + comp + "' is not defined.", instruction.line_number);
                errors.push_back(error);
                comp_bin = comp_table.at("0");
            }

            if (jump.empty())
                jump_bin = jump_table.at("null");
            else if (jump_table.contains(jump))
                jump_bin = jump_table.at(jump);
            else
            {
                auto error = AssembleError("A 'jump' part named '" + jump + "' is not defined.", instruction.line_number);
                errors.push_back(error);
                jump_bin = jump_table.at("null");
            }

            line = "111";
            line.append(comp_bin);
            line.append(dest_bin);
            line.append(jump_bin);
        }
        else
            continue;

        code.push_back(line);
    }

    return errors.empty();
}
