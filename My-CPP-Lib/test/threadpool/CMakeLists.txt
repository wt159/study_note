cmake_minimum_required(VERSION 3.0.0)
project(thread-pool-test VERSION 0.1.0)

include(CTest)
enable_testing()

set(C_STANDARD 11)
set(CXX_STANDARD 11)

set(INC_DIR ../../cpp)
include_directories("${INC_DIR}")

add_executable(thread-pool-test  ${INC_DIR}/ThreadPool.cpp main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
