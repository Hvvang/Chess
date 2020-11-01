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
            , type(type) {}

    const ChessSide &Piece::getSide() const {
        return side;
    }


    Position Piece::getDirection(const int &deltaX, const int &deltaY) {
        if (deltaX && deltaY) {
            return { deltaY / abs(deltaY), deltaX / abs(deltaX) };
        }
        else {

            return (!deltaY) ? Position(0, deltaX / abs(deltaX)) : Position(deltaY / abs(deltaY), 0);
        }
    }

//  returns MoveStatus after detection collision with other chess pieces:
//  if between currPos and nextPos is any piece, of if in spot with position equal
//  nextPos is ally piece we detect collision and so movement can`t be made
//  on another side movement can be made
    MoveStatus Piece::checkCollision(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;
        const auto &direction = getDirection(deltaX, deltaY);
        Position temp = currPos;

        do {
            temp = temp + direction;
            const auto &piece = board->getSpot(temp)->getPiece();

            if (piece) {
                if (temp != nextPos || getSide() == piece->getSide())
                    return MoveStatus::NotValid;
                else return MoveStatus::KillMove;
            }
        } while (temp != nextPos);
        return MoveStatus::Default;
    }

    const Types &Piece::getType() const {
        return type;
    }

//  returns a vector of position where current piece can move
//  checking on current piece can move to all field spots:
//  if true - adding pos of spot to vector, else - skip
    std::vector<Position> Piece::getAvailableMoves(const Position &currPos, Board *board) {
        std::vector<Position> availableMoves;

        for (const auto &spots : board->getField()) {
            for (const auto &it : spots) {
                if (currPos != it->getPos())
                    if (moveStrategy(currPos, it->getPos(), board) != MoveStatus::NotValid) {
                        availableMoves.push_back(it->getPos());
                    }
            }
        }
        return availableMoves;
    }

    bool Piece::isMoved() const {
        return Moved;
    }

    void Piece::setHasMoved(const bool &hasMoved) {
        Piece::Moved = hasMoved;
    }
}
