cmake_minimum_required(VERSION 3.7)
project(HW5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        .gitignore
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
        SymTable.h)

add_executable(HW5 ${SOURCE_FILES})