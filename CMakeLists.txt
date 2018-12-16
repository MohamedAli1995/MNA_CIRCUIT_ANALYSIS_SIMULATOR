cmake_minimum_required(VERSION 3.9)
project(MNA_circuits)

set(CMAKE_CXX_STANDARD 11)


message(STATUS "start running cmake...")

find_package(Boost COMPONENTS unit_test_framework REQUIRED)


# Unit tests
add_subdirectory(testbench)

include_directories(${Boost_INCLUDE_DIRS})


add_executable(MNA_circuits src/main.cpp src/Matrix.cpp src/Matrix.h src/Netlist.h src/Netlist.cpp src/Simulator.h )


target_link_libraries(MNA_circuits ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
