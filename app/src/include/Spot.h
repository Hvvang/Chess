//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_SPOT_H
#define CHESS_SPOT_H

#include "Piece.h"

namespace Chess {
class Piece;

    class Spot {
    public:
        Spot(Piece *piece = nullptr, const int &size = 50);
        ~Spot() = default;

        void setPiece(Piece *piece);

        [[nodiscard]] Piece *getPiece() const;

    private:
        Piece *piece;
        const int size;
    };
}

#endif //CHESS_SPOT_H
