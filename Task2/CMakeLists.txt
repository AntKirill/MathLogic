cmake_minimum_required(VERSION 3.6)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(Math_logic_HW2)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -w -O3")

set(MAIN_PROJECT_SOURCE_FILES test_all_main.cpp)

include_directories(proofing_library)
add_executable(${PROJECT_NAME} ${MAIN_PROJECT_SOURCE_FILES})
add_subdirectory(proofing_library)
target_link_libraries(${PROJECT_NAME} lib)