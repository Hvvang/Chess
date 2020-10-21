//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "Board.h"
#include "Piece.h"
#include "Player.h"

namespace Chess {
enum class MoveDirections {
    ForwardMove,
    BackwardMove,
    RightMove,
    LeftMove,
    DiagonalMove,
    AnotherMove, // knight
    NotValidStratege
};


class Move {
    Move(Board *board);


    bool isValidMove(Piece *piece, Position nextPos);

private:


private:
    static Board *board;
};
}


#endif //CHESS_MOVE_H
