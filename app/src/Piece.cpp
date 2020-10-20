//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Piece.h"

namespace Chess {
    Piece::Piece(const bool &side, std::pair<int, int> pos)
            : side(side)
            , x(pos.first)
            , y(pos.second) {};

    int Piece::getSide() const {
        return side;
    };

    std::pair<int, int> Piece::getPosition() const {
        return {x, y};
    }

    bool Piece::isKilled() const {
        return death;
    };

    void Piece::setDeath(const bool &death) {
        this->death = death;
    }

    void Piece::setPosition(std::pair<int, int> pos) {
        this->x = pos.first;
        this->y = pos.second;
    }
}
