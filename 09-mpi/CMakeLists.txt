cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})


add_executable(ex1 ex1.c)
target_link_libraries(ex1 ${MPI_C_LIBRARIES})
target_compile_options(ex1 PRIVATE -Wall -Wextra -pedantic)