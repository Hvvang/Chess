//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Spot.h"

namespace Chess {
    Spot::Spot(Piece *piece, const int &size)
            : size(size)
            , piece(piece) {};

    void Spot::setPiece(Piece *piece) {
        this->piece = piece;
    }

    Piece *Spot::getPiece() const {
        return piece;
    }
}


