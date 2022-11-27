cmake_minimum_required(VERSION 3.20.2)
project(ex1)

set(CPP_FILES main.cpp, main23a1.cpp, wet1util.h, worldcup23a1.cpp, worldcup23a1.h, AvlTree.h, WorldCup.h)
add_executable(ex1 main.cpp AvlTree.h Pair.h Player.h Team.h WorldCup.h Score.h )