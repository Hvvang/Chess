//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Knight.h"
#include <iostream>
namespace Chess {
    Knight::Knight(const ChessSide &side)
            : Piece(side) {}

    MoveStatus Knight::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) * abs(deltaY) == 2) {
            return checkCollision(currPos, nextPos, board);
        }
        return MoveStatus::NotValid;
    }

    MoveStatus Knight::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        const auto &piece = board->getSpot(nextPos)->getPiece();

        std::cout << "currPos = " << currPos.first << " " << currPos.second << std::endl;
        std::cout << "nextPos = " << nextPos.first << " " << nextPos.second << std::endl;
        if (piece != nullptr) {
            if (this->getSide() != piece->getSide())
                return MoveStatus::KillMove;
            else return MoveStatus::NotValid;
        } else {
            return MoveStatus::Default;
        }
    }
}
