//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const ChessSide &side)
            : Piece(side, Types::Pawn) {}

    MoveStatus Pawn::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
//      deltaX - movement`s offset by Y coordinate
//      deltaY - movement`s offset by X coordinate
        auto deltaX = nextPos.second - currPos.second;
        auto deltaY = nextPos.first - currPos.first;

//      disable movement if offset more than:
//          2 spots forward or backward,
//          1 spot left or right,
//          1 spot by diagonal move
        if (abs(deltaX) > 1 || abs(deltaY) > 2 || abs(deltaX) * abs(deltaY) > 1) {
            return MoveStatus::NotValid;
        }
//      disable movement 2 spots forward if pawn doesn't stand in 2nd row
        if (!(currPos.first == 1 || currPos.first == 6) && abs(deltaY) == 2) {
            return MoveStatus::NotValid;
        }
//      disable movement backward
        if ((this->getSide() == ChessSide::WHITE && deltaY > 0)
            || (this->getSide() == ChessSide::BLACK && deltaY < 0)) {
//          disable diagonal movement if spot to move is empty from opposite player piece
            if (abs(deltaX) == abs(deltaY) == 1 && !board->getSpot(nextPos)->getPiece()) {
                return MoveStatus::NotValid;
            }
            auto collision = checkCollision(currPos, nextPos, board);
//          check on pawn promotion (when pawn comes to the end of the bord)
            if (collision != MoveStatus::NotValid
                && (nextPos.first == 0 || nextPos.first == 7))
                return MoveStatus::PawnPromotion;
            return collision;
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