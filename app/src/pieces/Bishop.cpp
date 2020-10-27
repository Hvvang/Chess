//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const ChessSide &side)
            : Piece(side) {}

    MoveStatus Bishop::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY)) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}
