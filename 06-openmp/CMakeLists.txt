cmake_minimum_required(VERSION 3.12.1)
project(OpenMP_exercises C)
include(FindOpenMP)
if(NOT OPENMP_C_FOUND)
    message(FATAL_ERROR "OpenMP could not be found.")
endif(NOT OPENMP_C_FOUND)

add_executable(matrix_multiply_add matrix_multiply_add.c)
target_link_libraries(matrix_multiply_add PRIVATE OpenMP::OpenMP_C)
target_compile_options(matrix_multiply_add PRIVATE -Wall -Wextra -pedantic)

add_executable(matrix_multiply_add_serial matrix_multiply_add_serial.c)
target_compile_options(matrix_multiply_add_serial PRIVATE -Wall -Wextra -pedantic)

add_executable(sections sections.c)
target_link_libraries(sections PRIVATE OpenMP::OpenMP_C)
target_compile_options(sections PRIVATE -Wall -Wextra -pedantic)
