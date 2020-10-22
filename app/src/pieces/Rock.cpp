//
// Created by Artem Shemidko on 20.10.2020.
//

#include "Rock.h"


namespace Chess {
    Rock::Rock(const bool &side, const Position &pos)
        : Piece(side, pos) {}

    bool Rock::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (!deltaX || !deltaY) {
            return checkCollision(currPos, nextPos, board);
        } else return false;
    }
}


