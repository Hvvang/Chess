cmake_minimum_required(VERSION 3.17)
project(chess)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_EXE main.cpp)

include_directories(
        ../3dparty/sfml/include
        src/include
        src/pieces/include
)

configure_file(res/board.png ${CMAKE_CURRENT_BINARY_DIR}/board.png COPYONLY)
configure_file(res/figures.png ${CMAKE_CURRENT_BINARY_DIR}/figures.png COPYONLY)
configure_file(res/sansation.ttf ${CMAKE_CURRENT_BINARY_DIR}/sansation.ttf COPYONLY)

add_executable(chess ${SOURCE_EXE})

add_subdirectory(src)
target_link_libraries(chess sfml-graphics sfml-window)
target_link_libraries(chess SRC_LIB)
