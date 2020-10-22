//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const ChessSide &side, const Position &pos)
            : Piece(side, pos) {}

    bool Bishop::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY)) {
            return checkCollision(currPos, nextPos, board);
        } else return false;
    }
}
