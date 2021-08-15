#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Assembler.h"

int main(int argc, char **argv) {
    // Read command line arguments.
    if (argc == 1)
    {
        std::cerr << "Warning: No source files specified." << std::endl;
        return 0;
    }
    auto file_name = std::string(argv[1]);

    // Read assembly code.
    std::ifstream input_file(file_name);
    if (!input_file.is_open())
    {
        std::cerr << "Error: Source file '" << file_name
                    << "' could not open." << std::endl;
        return 0;
    }
    std::vector<std::string> source;
    for (std::string line; getline(input_file, line); )
        source.push_back(line);
    input_file.close();

    // Assemble source code.
    Assembler assembler(source);
    std::vector<std::string> code;
    assembler.assemble(code);

    // TODO: Write binary code.

    return 0;
}
