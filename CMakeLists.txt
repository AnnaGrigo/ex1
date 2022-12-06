cmake_minimum_required(VERSION 3.20.2)
project(ex1)

set(CPP_FILES main.cpp wet1util.h  AvlTree.h Player.h Player.cpp Score.h Team.h Team.cpp worldcup23a1.h worldcup23a1.cpp )
add_executable(ex1 ${CPP_FILES})