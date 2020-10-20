//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Spot.h"

namespace Chess {
    Spot::Spot(const int &x, const int &y, Piece *piece, const int &size)
            : x(x)
            , y(y)
            , size(size)
            , piece(piece) {};

    void Spot::setPiece(Piece *piece) {
        this->piece = piece;
    }

    int Spot::getX() const {
        return x;
    };

    int Spot::getY() const {
        return y;
    };

    Piece *Spot::getPiece() const {
        return piece;
    }
}


