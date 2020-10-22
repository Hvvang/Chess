//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "King.h"

namespace Chess {
    King::King(const bool &side, const Position &pos)
            : Piece(side, pos) {}

    bool King::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) * abs(deltaY) <= 1) {
            return checkCollision(currPos, nextPos, board);
        } else return false;
    }
}
