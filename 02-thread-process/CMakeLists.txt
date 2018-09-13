cmake_minimum_required(VERSION 3.12.1)
project(matrix_multiply C)
find_package(Threads REQUIRED)

add_executable(matrix_add_proc matrix_add_proc.c)
target_link_libraries(matrix_add_proc Threads::Threads)
