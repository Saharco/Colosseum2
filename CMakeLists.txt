cmake_minimum_required(VERSION 3.7)
project(Colosseum2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AVLTree.h GladiatorScores.cpp GladiatorScores.h)
add_executable(Colosseum2 ${SOURCE_FILES})