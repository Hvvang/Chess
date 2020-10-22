//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Knight.h"

namespace Chess {
    Knight::Knight(const bool &side, const Position &pos)
            : Piece(side, pos) {}

    bool Knight::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) * abs(deltaY) == 2) {
            return checkCollision(currPos, nextPos, board);
        }
        return false;
    }

    bool Knight::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        const auto &piece = board->getBoard()[nextPos.first][nextPos.second]->getPiece();

        if (piece != nullptr) {
            if (this->getSide() != piece->getSide())
                return true;
            else return false;
        } else {
            return true;
        }
    }
}
