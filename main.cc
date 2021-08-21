#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include "Assembler.h"

int main(int argc, char **argv)
{
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

    // Read assembly obj_code.
    std::ifstream input_file(file_path);
    if (!input_file.is_open())
    {
        std::cerr << "Error: Source file '" << file_path << "' could not open." << std::endl;
        return EXIT_FAILURE;
    }
    auto source = new std::vector<std::string>();
    for (std::string line; std::getline(input_file, line); )
    {
        source->push_back(line);
    }
    input_file.close();

    auto object_code = new std::vector<std::string>();
    Assembler assembler(source);
    assembler.assemble(object_code);

    // Write object obj_code.
    file_path.replace_extension(".hack");
    std::ofstream output_file(file_path);
    if (!output_file.is_open())
    {
        std::cerr << "Error: Object file '" << file_path << "' could not open." << std::endl;
        return EXIT_FAILURE;
    }
    for (const auto &line : *object_code)
        output_file << line << std::endl;
    output_file.close();

    delete object_code;

    return EXIT_SUCCESS;
}
