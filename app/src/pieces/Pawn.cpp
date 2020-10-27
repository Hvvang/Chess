//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const ChessSide &side)
            : Piece(side, Types::Pawn) {}

    MoveStatus Pawn::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (abs(deltaX) > 1 || abs(deltaY) > 2 || abs(deltaX) * abs(deltaY) > 1) {
            return MoveStatus::NotValid;
        }
        if (!(currPos.first == 1 || currPos.first == 6) && abs(deltaY) == 2) {
            return MoveStatus::NotValid;
        }
        if ((this->getSide() == ChessSide::WHITE && deltaY > 0)
            || (this->getSide() == ChessSide::BLACK && deltaY < 0)) {
            if (abs(deltaX) == abs(deltaY) == 1 && !board->getSpot(nextPos)->getPiece()) {
                return MoveStatus::NotValid;
            }
            return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }

    MoveStatus Pawn::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        auto collision = Piece::checkCollision(currPos, nextPos, board);
        if (collision != MoveStatus::NotValid) {
            auto deltaY = nextPos.first - currPos.first;
            auto deltaX = nextPos.second - currPos.second;
            auto currPiece = board->getSpot(currPos)->getPiece();
            auto nextPiece = board->getSpot(nextPos)->getPiece();

            if (abs(deltaX) == abs(deltaY) == 1) {
                if (!nextPiece)
                    return MoveStatus::NotValid;
                else if (nextPiece && nextPiece->getSide() == currPiece->getSide())
                    return MoveStatus::NotValid;
                else return MoveStatus::KillMove;
            }
            if (!deltaX && nextPiece) {
                return MoveStatus::NotValid;
            }
            return MoveStatus::Default;
        }
        return collision;
    };
}