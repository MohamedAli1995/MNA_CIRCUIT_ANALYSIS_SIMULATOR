# CMakeList.txt : CMake project for assignment2_modeling, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
# Add source to this project's executable.
add_executable (assignment2modeling "assignment2_modeling.cpp" "assignment2_modeling.h" "Matrix.cpp" "Matrix.h"  "Netlist.cpp" "Netlist.h" "Simulator.h" "Simulator.cpp")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
# TODO: Add tests and install targets if needed.
