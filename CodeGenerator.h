//
// Created by Kosuke Futamata on 21/08/2021.
//

#include <vector>
#include <map>
#include <sstream>
#include <bitset>
#include <iostream>
#include "Instruction.h"


class CodeGenerator
{
    const std::map<std::string, std::string> comp_table
    {
        { "0", "0101010"},
        { "1", "0111111" },
        { "-1", "0111010" },
        { "D","0001100", },
        { "A", "0110000", },
        { "M", "1110000", },
        { "!D", "0001100" },
        { "!A", "0110001" },
        { "!M", "1110001" },
        { "-D", "0001111" },
        { "-A", "0110011" },
        { "-M", "1110011" },
        { "D+1", "0011111" },
        { "A+1", "0110111" },
        { "M+1", "1110111" },
        { "D-1", "0001110" },
        { "A-1", "0110010" },
        { "M-1", "1110010" },
        { "D+A", "0000010" },
        { "D+M", "1000010" },
        { "D-A", "0010011" },
        { "D-M", "1010011" },
        { "A-D", "0000111" },
        { "M-D", "1000111" },
        { "D&A", "0000000" },
        { "D&M", "1000000" },
        { "D|A", "0010101" },
        { "D|M", "1010101" }
    };
    const std::map<std::string, std::string> dest_table
    {
        { "null", "000" },
        { "M", "001" },
        { "D", "010" },
        { "MD", "011" },
        { "A", "100" },
        { "AM", "101" },
        { "AD", "110" },
        { "AMD", "111" }
    };
    const std::map<std::string, std::string> jump_table
    {
        { "null", "000" },
        { "JGT", "001" },
        { "JEQ", "010" },
        { "JGE", "011" },
        { "JLT", "100" },
        { "JNE", "101" },
        { "JLE", "110" },
        { "JMP", "111" }
    };
    std::vector<Instruction*> *instructions;
    std::map<std::string, int> *symbol_table;
public:
    explicit CodeGenerator(std::vector<Instruction*> *instructions, std::map<std::string, int> *symbol_table)
        : instructions(instructions), symbol_table(symbol_table)
    {
    }

    void generate(std::vector<std::string> *object_code)
    {
        for (auto instruction : *instructions)
        {
            std::string line;
            switch (instruction->kind)
            {
                case InstructionKind::C_COMMAND:
                {
                    std::string dest, comp, jump;
                    if (instruction->dest.empty())
                        dest = dest_table.at("null");
                    else if (dest_table.contains(instruction->dest))
                        dest = dest_table.at(instruction->dest);
                    else
                    {
                        std::cerr << "Error: '" + instruction->dest + "' is undefined instruction." << std::endl;
                        continue;
                    }
                    if (instruction->comp.empty())
                    {
                        std::cerr << "Error: Undefined instruction." << std::endl;
                        continue;
                    }
                    else if (comp_table.contains(instruction->comp))
                        comp = comp_table.at(instruction->comp);
                    else
                    {
                        std::cerr << "Error: '" + instruction->comp + "' is undefined instruction." << std::endl;
                        continue;
                    }
                    if (instruction->jump.empty())
                        jump = jump_table.at("null");
                    else if (jump_table.contains(instruction->jump))
                        jump = jump_table.at(instruction->jump);
                    else
                    {
                        std::cerr << "Error: '" + instruction->jump + "' is undefined instruction." << std::endl;
                        continue;
                    }
                    line = "111";
                    line.append(comp);
                    line.append(dest);
                    line.append(jump);
                    break;
                }
                case InstructionKind::L_COMMAND:
                {
                    continue;
                }
                case InstructionKind::A_COMMAND:
                {
                    int address;
                    if (instruction->is_numeric)
                        address = std::stoi(instruction->symbol);
                    else
                        address = symbol_table->at(instruction->symbol);
                    std::stringstream ss;
                    ss << std::bitset<15>(address);
                    line = "0" + ss.str();
                    break;
                }
            }
            object_code->push_back(line);
        }
    }
};