//
// Created by Artem Shemidko on 22.10.2020.
//

#include "Rock.h"

namespace Chess {

    Rock::Rock(const ChessSide &side)
        : Piece(side, Types::Rock) {}

    MoveStatus Rock::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (!deltaX || !deltaY) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}