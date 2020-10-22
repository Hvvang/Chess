//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const ChessSide &side, const Position &pos)
            : Piece(side, pos) {}

    bool Pawn::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (abs(deltaX) > 1 || abs(deltaY) > 2 || abs(deltaX) * abs(deltaY) > 1) {
            return false;
        }
        if (!(currPos.first == 1 || currPos.first == 6) && abs(deltaY) == 2) {
            return false;
        }
        if ((this->getSide() == ChessSide::WHITE && deltaY > 0)
            || (this->getSide() == ChessSide::BLACK && deltaY < 0)) {
            if (abs(deltaX) == abs(deltaY) == 1 && !board->getSpot(nextPos)) {
                return false;
            }
            return checkCollision(currPos, nextPos, board);
        } else return false;
    }

    bool Pawn::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        if (Piece::checkCollision(currPos, nextPos, board)) {
            auto deltaY = nextPos.first - currPos.first;
            auto deltaX = nextPos.second - currPos.second;

            if (abs(deltaX) == abs(deltaY) == 1 && !board->getSpot(nextPos)) {
                return false;
            }
            if (!deltaX && board->getSpot(nextPos)) {
                return false;
            }
            return true;
        }
        return false;
    };
}