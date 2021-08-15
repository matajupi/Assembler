//
// Created by Kosuke Futamata on 16/08/2021.
//

#ifndef ASSEMBLER_ASSEMBLER_H
#define ASSEMBLER_ASSEMBLER_H


#include <string>
#include <vector>


class Assembler {
private:
    const std::vector<std::string> source;
public:
    explicit Assembler(std::vector<std::string>&);
    void assemble(std::vector<std::string>&);
};


#endif //ASSEMBLER_ASSEMBLER_H
