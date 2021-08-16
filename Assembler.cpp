//
// Created by Kosuke Futamata on 16/08/2021.
//

#include "Assembler.h"

Assembler::Assembler(std::vector<std::string> &source) : source(source)
{
}

bool Assembler::assemble(std::vector<std::string> &code, std::vector<AssembleError> &errors)
{
    // Split assembly code into instructions.
    Parser parser(this->source);
    std::vector<Instruction> instructions;
    if (!parser.parse(instructions, errors))
        return false;

    // Create symbol table.
    std::map<std::string, int> symbol_table;
    if (!create_symbol_table(symbol_table, instructions, errors))
        return false;

    // Generate object code.
    CodeGenerator generator(instructions, symbol_table);
    if (!generator.generate(code, errors))
        return false;
    return true;
}

bool Assembler::create_symbol_table(std::map<std::string, int> &symbol_table, std::vector<Instruction> &instructions, std::vector<AssembleError> &errors)
{
    // Predefined symbols.
    symbol_table["SP"] = 0;
    symbol_table["LCL"] = 1;
    symbol_table["ARG"] = 2;
    symbol_table["THIS"] = 3;
    symbol_table["THAT"] = 4;
    symbol_table["SCREEN"] = 16384;
    symbol_table["KBD"] = 24576;
    for (auto i = 0; 16 > i; i++)
    {
        auto symbol = "R" + std::to_string(i);
        symbol_table[symbol] = i;
    }

    // Put L_COMMAND symbols.
    auto line_number = 0;
    for (auto instruction : instructions)
    {
        if (instruction.type == InstructionType::L_COMMAND)
        {
            if (symbol_table.contains(instruction.symbol))
            {
                auto error = AssembleError("A label named '" + instruction.symbol + "' is already defined.", instruction.line_number);
                errors.push_back(error);
            }
            symbol_table[instruction.symbol] = line_number;
        }
        else
            line_number++;
    }

    // Put A_COMMAND symbols.
    auto memory_address = 16;
    auto variable_pattern = std::regex(R"([a-zA-Z_:\.\$][0-9a-zA-Z_:\.\$]*)");
    for (auto instruction : instructions)
    {
        if (instruction.type == InstructionType::A_COMMAND
        && !symbol_table.contains(instruction.symbol)
        && std::regex_match(instruction.symbol, variable_pattern))
            symbol_table[instruction.symbol] = memory_address++;
    }

    return errors.empty();
}
