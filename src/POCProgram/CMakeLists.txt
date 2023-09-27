# POCProgram/CMakeLists.txt

project(POCProgram)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(POCProgram TestPOC.cpp)

target_link_libraries(POCProgram GameEngine raylib)
