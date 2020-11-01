//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const ChessSide &side)
            : Piece(side, Types::Bishop) {}

//  available only diagonal move:
//  if nextPos is not on diagonal return NotValid move
//  else checking collision with other pieces between currPos and nextPos
    MoveStatus Bishop::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY)) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}
