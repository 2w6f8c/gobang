cmake_minimum_required(VERSION 3.14)
project(gobang)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

add_executable(gobang main.c def.h init.h init.c draw.h draw.c engine.h engine.c randomPlay.h randomPlay.c evaluate.h evaluate.c alphaBeta.h alphaBeta.c stack.h stack.c)