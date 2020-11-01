//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Knight.h"
#include <iostream>
namespace Chess {
    Knight::Knight(const ChessSide &side)
            : Piece(side, Types::Knight) {}

//  check for considering the impossibility of any move
//  that isn't 7-like move and collision with ally piece
    MoveStatus Knight::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        if (abs(deltaX) * abs(deltaY) == 2) {
            return checkCollision(currPos, nextPos, board);
        }
        return MoveStatus::NotValid;
    }

//  check collision with other piece
    MoveStatus Knight::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        const auto &piece = board->getSpot(nextPos)->getPiece();

        if (piece != nullptr) {
            if (this->getSide() != piece->getSide())
                return MoveStatus::KillMove;
            else return MoveStatus::NotValid;
        } else {
            return MoveStatus::Default;
        }
    }
}
