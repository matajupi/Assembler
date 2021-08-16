//
// Created by Kosuke Futamata on 16/08/2021.
//

#include "AssembleError.h"

AssembleError::AssembleError(const std::string& message, int line_number)
    : runtime_error(message), line_number(line_number)
{
}

void AssembleError::dump(std::ostream &ostream, std::filesystem::path &file_path)
{
    ostream << file_path.filename() << "(" << this->line_number << "): ";
    ostream << "AssembleError: " << what() << std::endl;
}
