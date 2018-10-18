cmake_minimum_required(VERSION 3.12.1)
project(OpenMP_exercises C)
include(FindOpenMP)
if(NOT OPENMP_C_FOUND)
    message(FATAL_ERROR "OpenMP could not be found.")
endif(NOT OPENMP_C_FOUND)

add_executable(linked-list linked-list.c)
target_link_libraries(linked-list PRIVATE OpenMP::OpenMP_C)
target_compile_options(linked-list PRIVATE -Wall -Wextra -pedantic)

add_executable(merge-sort merge-sort.c)
target_link_libraries(merge-sort PRIVATE OpenMP::OpenMP_C)
target_compile_options(merge-sort PRIVATE -Wall -Wextra -pedantic)

# add_executable(matrix_multiply_add_serial matrix_multiply_add_serial.c)
# target_compile_options(matrix_multiply_add_serial PRIVATE -Wall -Wextra -pedantic)
