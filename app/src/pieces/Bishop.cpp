//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const bool &side, const Position &pos)
            : Piece(side, pos) {}

    bool Bishop::moveStrategy(const Position &nextPos, const Board *board) {
        auto currPos = getPosition();
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        if (abs(deltaX) == abs(deltaY)) {
            const auto &direction = getDirection(currPos, nextPos);
            Position temp = currPos;
            do {
                temp = temp + direction;
                const auto &piece = board->getBoard()[temp.first][temp.second]->getPiece();
                if (piece != nullptr) {
                    if (temp != nextPos)
                        return false;
                    else if (this->getSide() == piece->getSide())
                        return false;
                    else return true;
                }
            } while (temp != nextPos);
        } else return false;
    }

    Position Bishop::getDirection(const Position &currPos, const Position &nextPos) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;

        return { deltaX / abs(deltaX), deltaY / abs(deltaY) };
    }



}
