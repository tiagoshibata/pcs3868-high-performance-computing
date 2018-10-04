cmake_minimum_required(VERSION 3.12.1)
project(OpenMP_exercises C)
include(FindOpenMP)
if(NOT OPENMP_C_FOUND)
    message(FATAL_ERROR "OpenMP could not be found.")
endif(NOT OPENMP_C_FOUND)

add_executable(sum sum.c)
target_link_libraries(sum PRIVATE OpenMP::OpenMP_C)
target_compile_options(sum PRIVATE -Wall -Wextra -pedantic)

add_executable(find_element find_element.c)
target_link_libraries(find_element PRIVATE OpenMP::OpenMP_C)
target_compile_options(find_element PRIVATE -Wall -Wextra -pedantic)
