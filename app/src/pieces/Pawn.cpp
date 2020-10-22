//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const bool &side, const Position &pos)
            : Piece(side, pos) {}

    bool Pawn::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) > 1 || abs(deltaY) > 2 || abs(deltaX) * abs(deltaY) > 1)
            return false;
        if (abs(nextPos.second + 1 - BOARD_ROWS) > 4 && abs(deltaY) == 2) {
            return false;
        }
        if ((this->getSide() == WHITE && deltaY > 0)
            || (this->getSide() == BLACK && deltaY < 0)) {
            return checkCollision(currPos, nextPos, board);
        } else return false;
    };
}