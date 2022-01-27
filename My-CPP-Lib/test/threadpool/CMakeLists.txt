cmake_minimum_required(VERSION 3.0.0)
project(thread-pool-test VERSION 0.1.0)

set(CMAKE_C_COMPILER C:/msys64/mingw64/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/msys64/mingw64/bin/g++.exe)

# set(CXX /c/MinGW/bin/g++.exe)
# set(CC /c/MinGW/bin/gcc.exe)

set(C_STANDARD 11)
set(CXX_STANDARD 11)

set(INC_DIR ../../cpp)
include_directories("${INC_DIR}")

add_executable(thread-pool-test  ${INC_DIR}/ThreadPool.cpp main.cpp)
