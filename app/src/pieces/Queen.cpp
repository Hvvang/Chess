//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Queen.h"

namespace Chess {
    Queen::Queen(const ChessSide &side)
            : Piece(side, Types::Queen) {}

//  allow moving like rock and bishop at one time
//  and also check collision during this move
    MoveStatus Queen::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY) || (!deltaX || !deltaY)) {
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }
}
