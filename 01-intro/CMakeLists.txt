cmake_minimum_required(VERSION 3.12.1)
project(OpenMP_intro C)
include(FindOpenMP)
if(NOT OPENMP_C_FOUND)
    message(FATAL_ERROR "OpenMP could not be found.")
endif(NOT OPENMP_C_FOUND)

add_executable(parallel parallel.c)
target_link_libraries(parallel PRIVATE OpenMP::OpenMP_C)
