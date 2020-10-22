//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Piece.h"

namespace Chess {
    Piece::Piece(const bool &side, Position pos)
            : side(side)
            , pos(pos) {};

    int Piece::getSide() const {
        return side;
    };

    Position Piece::getPosition() const {
        return pos;
    }

    bool Piece::isKilled() const {
        return death;
    };

    void Piece::setDeath(const bool &death) {
        this->death = death;
    }

    void Piece::setPosition(Position pos) {
        this->pos = pos;
    }

    bool Piece::canMove(Position nextPos, Board *board) {
        if (Piece::moveStrategy(nextPos, board)) {
            return true;
        }
        return false;
    }

    Position Piece::getDirection(const int &deltaX, const int &deltaY) {
        if (deltaX && deltaY) {
            return { deltaX / abs(deltaX), deltaY / abs(deltaY) };
        }
        else {
            if (!deltaX) {
                return { 0, deltaY / abs(deltaY) };
            } else {
                return { deltaX / abs(deltaX), 0 };
            }
        }
    }

    bool Piece::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaX = nextPos.first - currPos.first;
        auto deltaY = nextPos.second - currPos.second;
        const auto &direction = getDirection(deltaX, deltaY);
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
    }

}
