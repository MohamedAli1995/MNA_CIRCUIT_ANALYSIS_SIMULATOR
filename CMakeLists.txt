cmake_minimum_required(VERSION 3.9)
project(MNA_circuits)
#enable_testing()
set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
SET(SourceDir src)
SET(TestDir testbench)


FILE(GLOB_RECURSE  SourceFilesWithMain ${SourceDir}/main.cpp  ${SourceDir}/Matrix.cpp  ${SourceDir}/Matrix.h  ${SourceDir}/Netlist.cpp  ${SourceDir}/Netlist.h  ${SourceDir}/Simulator.h)
FILE(GLOB_RECURSE  SourceFiles  ${SourceDir}/Matrix.cpp  ${SourceDir}/Matrix.h  ${SourceDir}/Netlist.cpp  ${SourceDir}/Netlist.h  ${SourceDir}/Simulator.h)


add_executable(MNA_circuit ${SourceFilesWithMain})
add_executable(demo1 ${TestDir}/demo1.cpp ${SourceFiles})
add_executable(demo2 ${TestDir}/demo2.cpp ${SourceFiles})
#add_executable(demo3 ${TestDir}/demo3.cpp ${SourceFiles})
target_link_libraries(demo1 ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries(demo2 ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
#target_link_libraries(demo3 ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )

target_include_directories(demo1 PRIVATE ${SourceDir})
target_include_directories(demo2 PRIVATE ${SourceDir})

### indicates the include paths
#target_include_directories(demo1 PRIVATE ${BOOST_INCLUDE_DIRS})

### declares a test with our executable
#add_test(NAME test1  COMMAND demo1  )
