cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI REQUIRED)

add_executable(ex1 ex1.c)
target_include_directories(ex1 PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(ex1 PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(ex1 PRIVATE ${MPI_C_LIBRARIES})


add_executable(parallel-search parallel-search.c)
target_include_directories(parallel-search PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(parallel-search PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(parallel-search PRIVATE ${MPI_C_LIBRARIES})
