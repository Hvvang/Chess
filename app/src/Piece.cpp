//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Piece.h"

namespace Chess {
    Position operator+(const Position &left, const Position &right) {
        return {left.first + right.first, left.second + right.second};
    }

    Piece::Piece(const ChessSide &side, const Position &pos)
            : side(side)
            , pos(pos) {};

    const ChessSide &Piece::getSide() const {
        return side;
    };

    const Position &Piece::getPosition() const {
        return pos;
    }

    const bool &Piece::isKilled() const {
        return death;
    };

    void Piece::setDeath(const bool &death) {
        this->death = death;
    }

    void Piece::setPosition(Position pos) {
        this->pos = pos;
    }

    bool Piece::canMove(Position nextPos, Board *board) {
        if (moveStrategy(nextPos, board)) {
            std::cout << "piw" << std::endl;
            return true;
        }
        std::cout << "paf" << std::endl;
        return false;
    }

    Position Piece::getDirection(const int &deltaX, const int &deltaY) {
        if (deltaX && deltaY) {
            return { deltaY / abs(deltaY), deltaX / abs(deltaX) };
        }
        else {
            if (!deltaY) {
                return { 0, deltaX / abs(deltaX) };
            } else {
                return { deltaY / abs(deltaY), 0 };
            }
        }
    }

    bool Piece::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;
        const auto &direction = getDirection(deltaX, deltaY);
        Position temp = currPos;

        do {
            temp = temp + direction;
            const auto &piece = board->getSpot(temp);

            std::cout << "TEPM: " << temp.first << " " << temp.second << std::endl;
            if (piece != nullptr) {
                if (temp != nextPos)
                    return false;
                else if (this->getSide() == piece->getSide())
                    return false;
                else return true;
            }
        } while (temp != nextPos);
        return true;
    }

    bool Piece::moveStrategy(const Position &nextPos, const Board *board) {
        return false;
    }
}
