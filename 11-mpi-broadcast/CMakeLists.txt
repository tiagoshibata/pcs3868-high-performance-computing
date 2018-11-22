cmake_minimum_required(VERSION 3.12.1)
project(MPI_exercises C)
find_package(MPI REQUIRED)

add_executable(search-in-matrix search-in-matrix.c)
target_include_directories(search-in-matrix PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(search-in-matrix PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(search-in-matrix PRIVATE ${MPI_C_LIBRARIES})

add_executable(01-search-occurrence 01-search-occurrence.c)
target_include_directories(01-search-occurrence PRIVATE ${MPI_INCLUDE_PATH})
target_compile_options(01-search-occurrence PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(01-search-occurrence PRIVATE ${MPI_C_LIBRARIES})
