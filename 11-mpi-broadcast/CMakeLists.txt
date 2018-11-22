cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI REQUIRED)

add_executable(search-in-matrix search-in-matrix.c)
target_include_directories(search-in-matrix PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(search-in-matrix PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(search-in-matrix PRIVATE ${MPI_C_LIBRARIES})
