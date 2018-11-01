cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})


add_executable(trivial trivial.c)
target_link_libraries(trivial ${MPI_C_LIBRARIES})
target_compile_options(trivial PRIVATE -Wall -Wextra -pedantic)