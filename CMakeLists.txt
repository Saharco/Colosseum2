cmake_minimum_required(VERSION 3.7)
project(Colosseum2)

set(CMAKE_CXX_STANDARD 98)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98 -Wall")
set(SOURCE_FILES main2.cpp HashTable.h List.h MinHeap.h AVLTree.h Colosseum.cpp Colosseum.h
        GladiatorGroup.h GladiatorGroup.cpp library2.h libary2.cpp)
add_executable(Colosseum2_final ${SOURCE_FILES})