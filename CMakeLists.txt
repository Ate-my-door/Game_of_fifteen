cmake_minimum_required(VERSION 3.10)

project(GAME_OF_FIFTEEN CXX)

add_executable(fifteen fifteen.cpp)

add_compile_options(fifteen PUBLIC cxx_std_14 Wall)
