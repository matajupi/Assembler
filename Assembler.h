//
// Created by Kosuke Futamata on 21/08/2021.
//

#include <vector>
#include <string>
#include <map>
#include "Parser.h"
#include "Instruction.h"
#include "CodeGenerator.h"


class Assembler
{
    std::vector<std::string> *source;
public:
    explicit Assembler(std::vector<std::string> *source) : source(source) { }
    void assemble(std::vector<std::string> *object_code)
    {
        Parser parser(source);
        auto instructions = new std::vector<Instruction*>();
        parser.parse(instructions);

        // Create symbol_table
        auto symbol_table = new std::map<std::string, int>
        {
            { "SP", 0 },
            { "LCL", 1 },
            { "ARG", 2 },
            { "THIS", 3 },
            { "THAT", 4 },
            { "SCREEN", 16384 },
            { "KBD", 24576 },
            { "R0", 0 },
            { "R1", 1 },
            { "R2", 2 },
            { "R3", 3 },
            { "R4", 4 },
            { "R5", 5 },
            { "R6", 6 },
            { "R7", 7 },
            { "R8", 8 },
            { "R9", 9 },
            { "R10", 10 },
            { "R11", 11 },
            { "R12", 12 },
            { "R13", 13 },
            { "R14", 14 },
            { "R15", 15 },
        };

        auto line_number = 0;
        for (auto instruction : *instructions)
        {
            if (instruction->kind == InstructionKind::L_COMMAND)
            {
                if (symbol_table->contains(instruction->symbol))
                {
                    std::cerr << "Error: The label name '" << instruction->symbol << "' is already defined." << std::endl;
                    continue;
                }
                (*symbol_table)[instruction->symbol] = line_number;
            }
            else
                line_number++;
        }

        auto address = 16;
        for (auto instruction : *instructions)
        {
            if (instruction->kind == InstructionKind::A_COMMAND && !instruction->is_numeric)
            {
                if (symbol_table->contains(instruction->symbol))
                    continue;
                (*symbol_table)[instruction->symbol] = address++;
            }
        }

        CodeGenerator generator(instructions, symbol_table);
        generator.generate(object_code);
    }
};
