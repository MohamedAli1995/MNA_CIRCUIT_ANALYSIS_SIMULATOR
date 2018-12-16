cmake_minimum_required(VERSION 3.9)
project(MNA_circuits)

set(CMAKE_CXX_STANDARD 11)

add_executable(MNA_circuits main.cpp  Matrix.cpp Matrix.h Netlist.h Netlist.cpp Simulator.h)