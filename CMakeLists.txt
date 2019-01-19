cmake_minimum_required(VERSION 3.7)
project(HW5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bp.cpp
        bp.hpp
        Exceptions.h
        Node.cpp
        Node.h
        output.cpp
        output.hpp
        parser.ypp
        scanner.lex
        StructType.cpp
        StructType.h
        SymTable.cpp
        SymTable.h
        binary_operators.h
        binary_operators.cpp
        register_handler.cpp
        register_handler.h
        utils.cpp
        utils.h
        comparison_operators.h
        comparison_operators.cpp
        func_generation.cpp
        func_generation.h parser_code.cpp parser_code.h)

add_executable(HW5 ${SOURCE_FILES})