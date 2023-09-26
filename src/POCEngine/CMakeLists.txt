project(POCEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(POCEngine POCEngine.cpp)

find_package(Threads REQUIRED)
target_link_libraries(POCEngine GameEngine RenderEngineLib AudioEngineLib dl Threads::Threads)
