cmake_minimum_required(VERSION 3.7)

project(Math_logic_HW3_proofing_library)

set (SOURCES generator.cpp)

set (HEADERS generator.h)

set (TEXTS proofing_templates/base.in)

add_library (lib ${SOURCES} ${HEADERS} ${TEXTS})