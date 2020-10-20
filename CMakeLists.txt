cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        src/include
        src/pieces/include
)

add_executable(chess main.cpp)

add_subdirectory(src)
target_link_libraries(chess SRC_LIB)
