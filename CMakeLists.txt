cmake_minimum_required(VERSION 3.10)
project(RISCV)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -O3 -std=c++11 -g")
add_executable(code main.cpp BitOperation.cpp BitOperation.h BTB.cpp BTB.h Execution.cpp Execution.h InstructionDecode.cpp InstructionDecode.h InstructionFetch.cpp InstructionFetch.h Memory.h MemoryAccess.cpp MemoryAccess.h Pipeline.cpp Pipeline.h Register.h WriteBack.cpp WriteBack.h)
