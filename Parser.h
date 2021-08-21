//
// Created by Kosuke Futamata on 21/08/2021.
//

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Instruction.h"


class Parser
{
    std::vector<std::string> *source;

    // chunks = line.Split(' ');
    static void get_chunks(const std::string& line, std::vector<std::string> *chunks, char sep)
    {
        std::stringstream ss(line);
        for (std::string chunk; std::getline(ss, chunk, sep); )
        {
            if (chunk.empty())
                continue;
            chunks->push_back(chunk);
        }
    }

public:
    explicit Parser(std::vector<std::string> *source) : source(source) { }

    void parse(std::vector<Instruction*> *instructions)
    {
        auto chunks = new std::vector<std::string>();
        for (std::string &line : *source)
        {
            get_chunks(line, chunks, ' ');
            parse_one_line(chunks, instructions);
            chunks->clear();
        }
        delete chunks;
    }

    static void parse_one_line(std::vector<std::string> *chunks, std::vector<Instruction*> *instructions)
    {
        for (auto iter = std::begin(*chunks); std::end(*chunks) != iter; iter++)
        {
            if (iter->size() >= 2 && iter->at(0) == '/' && iter->at(1) == '/')
            {
                // COMMENT
                return;
            }
            if (iter->size() > 1 && iter->at(0) == '@')
            {
                // A_COMMAND
                auto symbol = iter->substr(1);

                auto is_numeric = true;
                for (auto c : symbol)
                    is_numeric = std::isdigit(c) && is_numeric;

                if (symbol.empty() || !is_numeric && std::isdigit(symbol.at(0)))
                {
                    std::cerr << "Error: The variable name '" + symbol + "' is invalid." << std::endl;
                    continue;
                }

                auto instruction = new Instruction();
                instruction->kind = InstructionKind::A_COMMAND;
                instruction->symbol = symbol;
                instruction->is_numeric = is_numeric;
                instructions->push_back(instruction);
                continue;
            }
            if (iter->size() > 1 && iter->at(0) == '(')
            {
                // L_COMMAND
                auto symbol = iter->substr(1, iter->size() - 2);

                if (symbol.empty() || iter->at(iter->size() - 1) != ')'
                        || std::isdigit(symbol.at(0)))
                {
                    std::cerr << "Error: The label name '" + symbol + "' is invalid." << std::endl;
                    continue;
                }

                auto instruction = new Instruction();
                instruction->kind = InstructionKind::L_COMMAND;
                instruction->symbol = symbol;
                instructions->push_back(instruction);
                continue;
            }
            // C_COMMAND
            std::string dest, comp, jump;
            auto begin_comp = std::size_t(0);
            auto end_comp = iter->size();
            auto pos = iter->find("=");
            if (pos != std::string::npos)
            {
                dest = iter->substr(0, pos);
                begin_comp = pos + 1;
            }
            pos = iter->find(";");
            if (pos != std::string::npos)
            {
                jump = iter->substr(pos + 1);
                end_comp = pos;
            }
            if (begin_comp >= end_comp)
            {
                std::cerr << "Error: The 'C Command' requires 'comp' part." << std::endl;
                continue;
            }
            comp = iter->substr(begin_comp, end_comp - begin_comp);
            auto instruction = new Instruction();
            instruction->kind = InstructionKind::C_COMMAND;
            instruction->dest = dest;
            instruction->comp = comp;
            instruction->jump = jump;
            instructions->push_back(instruction);
        }
    }

};
