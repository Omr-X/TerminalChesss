cmake_minimum_required(VERSION 4.1)
project(chess)

set(CMAKE_CXX_STANDARD 20)

add_executable(chess main.cpp
        ChessMoves.h
        Board/Node.cpp
        Move/Tile.h
        Pieces/PieceType.h
        Move/Move.h
)
