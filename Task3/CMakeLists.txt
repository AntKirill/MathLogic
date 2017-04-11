cmake_minimum_required(VERSION 3.7)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(Math_logic_HW3)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -w -O0")

set(MAIN_PROJECT_SOURCE_FILES main.cpp)

include_directories(proofing_library)
add_executable(${PROJECT_NAME} ${MAIN_PROJECT_SOURCE_FILES})
add_subdirectory(proofing_library)
target_link_libraries(${PROJECT_NAME} lib)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        	${CMAKE_SOURCE_DIR}/proofing_library/proofing_templates/base.in
        	${CMAKE_CURRENT_BINARY_DIR}/proofing_templates/base.in)