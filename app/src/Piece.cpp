//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Piece.h"

namespace Chess {
    Position operator+(const Position &left, const Position &right) {
        return {left.first + right.first, left.second + right.second};
    }

    Piece::Piece(const ChessSide &side, const Types &type)
            : side(side)
            , type(type) {};

    const ChessSide &Piece::getSide() const {
        return side;
    };

    const bool &Piece::isKilled() const {
        return death;
    };

    void Piece::setDeath(const bool &death) {
        this->death = death;
    }

    MoveStatus Piece::canMove(const Position &currPos, const Position &nextPos, Board *board) {
        return moveStrategy(currPos, nextPos, board);
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

    MoveStatus Piece::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;
        const auto &direction = getDirection(deltaX, deltaY);
        Position temp = currPos;

        do {
            temp = temp + direction;
            const auto &piece = board->getSpot(temp)->getPiece();

            if (piece) {
                if (temp != nextPos)
                    return MoveStatus::NotValid;
                else if (this->getSide() == piece->getSide())
                    return MoveStatus::NotValid;
                else return MoveStatus::KillMove;
            }
        } while (temp != nextPos);
        return MoveStatus::Default;
    }

    const Types &Piece::getType() const {
        return type;
    }

    std::vector<Position> Piece::getAvailibleMoves(const Position &currPos, Board *board) {
        std::vector<Position> availableMoves;

        for (const auto &spots : board->getBoard()) {
            for (const auto &it : spots) {
                if (currPos != it->getPos())
                    if (canMove(currPos, it->getPos(), board) != MoveStatus::NotValid) {
                        availableMoves.push_back(it->getPos());
                    }
            }
        }
        return availableMoves;
    }

    bool Piece::isHasMoved() const {
        return hasMoved;
    }

    void Piece::setHasMoved(const bool &hasMoved) {
        Piece::hasMoved = hasMoved;
    }
}
