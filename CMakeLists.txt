cmake_minimum_required(VERSION 3.10)

project(RTYPE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(GameEngine)
add_subdirectory(POCProgram)
add_subdirectory(RenderEngine)
add_subdirectory(AudioEngine)