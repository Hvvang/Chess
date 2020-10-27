//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "King.h"

namespace Chess {
    King::King(const ChessSide &side)
            : Piece(side, Types::King) {}

    MoveStatus King::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) <= 1 && abs(deltaY) <= 1) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}
