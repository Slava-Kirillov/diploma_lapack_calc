cmake_minimum_required(VERSION 3.15)
project(diploma_lapack_calc C)

set(CMAKE_C_STANDARD 99)

add_executable(diploma_lapack_calc main.c)

include_directories(/home/kirillov/Library/CLAPACK/INCLUDE)

#link_directories(/home/kirillov/Library/CLAPACK)

target_link_libraries(diploma_lapack_calc -llapack -lblas -lf2c -lm -lc)