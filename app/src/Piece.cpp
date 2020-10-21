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
}
