cmake_minimum_required(VERSION 3.6)

project(Math_logic_HW2_proofing_library)

set (SOURCES checker.cpp parser.cpp string_handler.cpp)

set (HEADERS checker.h parser.h tokens.h node.h axioms_and_assumptions.h string_handler.h)

add_library (lib ${SOURCES} ${HEADERS})