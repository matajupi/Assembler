cmake_minimum_required(VERSION 3.20)
project(Assembler)

set(CMAKE_CXX_STANDARD 23)

add_executable(Assembler main.cc assembler_all.h Parser.h Instruction.h CodeGenerator.h Assembler.h)
