cmake_minimum_required(VERSION 3.6)

project(Math_logic_HW2_proofing_library)

set (SOURCES checker.cpp parser.cpp string_handler.cpp proofer.cpp)

set (HEADERS checker.h parser.h tokens.h node.h axioms_and_assumptions.h string_handler.h proofer.h line_annotation.h)

include_directories(proof_generation_templates)

add_library (lib ${SOURCES} ${HEADERS})