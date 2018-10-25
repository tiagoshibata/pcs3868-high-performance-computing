cmake_minimum_required(VERSION 3.12.1)
project(OpenMP_exercises C)
include(FindOpenMP)
if(NOT OPENMP_C_FOUND)
    message(FATAL_ERROR "OpenMP could not be found.")
endif(NOT OPENMP_C_FOUND)

add_executable(aula8-ex1-deadlock aula8-ex1-deadlock.c)
target_link_libraries(aula8-ex1-deadlock PRIVATE OpenMP::OpenMP_C)
target_compile_options(aula8-ex1-deadlock PRIVATE -Wall -Wextra -pedantic)

add_executable(ex2-1-seq ex2-1-seq.c)
target_link_libraries(ex2-1-seq PRIVATE OpenMP::OpenMP_C)
target_compile_options(ex2-1-seq PRIVATE -Wall -Wextra -pedantic)
