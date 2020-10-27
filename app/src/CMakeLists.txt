cmake_minimum_required(VERSION 3.17)
project(chess)

include_directories(
        src/include
        src/pieces/include
)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Board.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Move.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Piece.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Spot.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/Bishop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/King.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/Knight.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/Pawn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/Queen.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/Rock.cpp
        )

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Board.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Game.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Move.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Piece.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Player.h
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Spot.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/Bishop.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/King.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/Knight.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/Pawn.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/Queen.h
        ${CMAKE_CURRENT_SOURCE_DIR}/pieces/include/Rock.h
)

add_library(SRC_LIB STATIC ${SOURCES} ${HEADERS})
