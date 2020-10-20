//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Piece.h"

namespace Chess {
    Piece::Piece(const bool &side)
            : side(side) {};

    int Piece::getSide() const {
        return side;
    };

    bool Piece::isKilled() const {
        return death;
    };

    void Piece::setDeath(const bool &death) {
        this->death = death;
    }
}
