#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Assembler.h"

int main(int argc, char **argv) {
    // Display assembler information.
    std::cout << "Hack assembler version 1.0" << std::endl;
    std::cout << "This is part of the nand2tetris project." << std::endl;
    std::cout << "See more information: https://www.nand2tetris.org/" << std::endl;
    std::cout << std::endl;

    // Read command line arguments.
    if (argc == 1)
    {
        std::cerr << "Error: No source files specified." << std::endl;
        return 0;
    }
    std::filesystem::path file_path = std::string(argv[1]);

    // Read assembly code.
    std::ifstream input_file(file_path);
    if (!input_file.is_open())
    {
        std::cerr << "Error: Source file '" << file_path << "' could not open." << std::endl;
        return 0;
    }
    std::vector<std::string> source;
    for (std::string line; getline(input_file, line); )
        source.push_back(line);
    input_file.close();

    // Assemble assembly code.
    Assembler assembler(source);
    std::vector<std::string> code;
    std::vector<AssembleError> errors;
    bool is_succeed;
    try
    {
        is_succeed = assembler.assemble(code, errors);
        if (!is_succeed)
        {
            for (auto error : errors)
                error.dump(std::cerr, file_path);
        }
    }
    catch (std::exception &ex)
    {
        std::cerr << "Internal assembler error: " << ex.what() << std::endl;
        std::cerr << "Please submit an issue to the following site with a full bug report and assembly code." << std::endl;
        std::cerr << "https://github.com/matajupi/HackAssembler/issues" << std::endl;
        is_succeed = false;
    }
    if (!is_succeed)
        return 0;

    // Write object code.
    file_path.replace_extension(".hack");
    std::ofstream output_file(file_path);
    if (!output_file.is_open())
    {
        std::cerr << "Error: Object file '" << file_path << "' could not open." << std::endl;
        return 0;
    }
    for (const auto& line : code)
        output_file << line << std::endl;
    output_file.close();

    return 0;
}
