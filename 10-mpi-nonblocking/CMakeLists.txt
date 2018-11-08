cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI REQUIRED)

add_executable(ex2 ex2.c)
target_include_directories(ex2 PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(ex2 PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(ex2 PRIVATE ${MPI_C_LIBRARIES})
