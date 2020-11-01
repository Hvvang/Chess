//
// Created by Artem Shemidko on 22.10.2020.
//

#include "Rock.h"

namespace Chess {

    Rock::Rock(const ChessSide &side)
        : Piece(side, Types::Rock) {}

//  allow moving only backward, forward, left or right considering collision with other pieces
    MoveStatus Rock::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (!deltaX || !deltaY) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}