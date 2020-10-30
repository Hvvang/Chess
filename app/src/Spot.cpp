//
// Created by Artem Shemidko on 27.10.2020.
//

#include "Spot.h"
#include "Queen.h"

namespace Chess {
    Spot::Spot(const Position &pos, Piece *piece)
        : pos(pos)
        , piece(piece) {

    }

    const Position &Spot::getPos() const {
        return pos;
    }

    Piece *Spot::getPiece() const {
        return piece;
    }

    void Spot::setPiece(Piece *piece) {
        Spot::piece = piece;
    }

    void Spot::pawnPromotion() {
        piece = new Queen(piece->getSide());
    }
}
