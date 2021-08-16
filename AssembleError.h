//
// Created by Kosuke Futamata on 16/08/2021.
//

#ifndef ASSEMBLER_ASSEMBLEERROR_H
#define ASSEMBLER_ASSEMBLEERROR_H


#include <filesystem>
#include <string>
#include <ostream>
#include <stdexcept>


class AssembleError : std::runtime_error {
public:
    const int line_number;
    AssembleError(const std::string& message, int line_number);
    void dump(std::ostream&, std::filesystem::path&);
};


#endif //ASSEMBLER_ASSEMBLEERROR_H
