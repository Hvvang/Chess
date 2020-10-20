cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_EXE main.cpp)

include_directories(
        ../3dparty/sfml/include
        src/include
        src/pieces/include
)

add_executable(chess ${SOURCE_EXE})

add_subdirectory(src)
target_link_libraries(chess sfml-graphics sfml-window sfml-system)
target_link_libraries(chess SRC_LIB)
