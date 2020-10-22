//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Queen.h"

namespace Chess {
    Queen::Queen(const bool &side, const Position &pos)
            : Piece(side, pos) {}

    bool Queen::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY) || (!deltaX || !deltaY)) {
            return checkCollision(currPos, nextPos, board);
        } else return false;
    }
}
