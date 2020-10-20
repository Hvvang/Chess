//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_SPOT_H
#define CHESS_SPOT_H

#include "Piece.h"

namespace Chess {
    class Spot {
    public:
        Spot(const int &x, const int &y, Piece *piece = nullptr, const int &size = 50);
        ~Spot() { delete piece; };

        void setPiece(Piece *piece);

        [[nodiscard]] Piece *getPiece() const;
        [[nodiscard]] int getX() const;
        [[nodiscard]] int getY() const;

    private:
        Piece *piece;
        const int size;
        const int x;
        const int y;
    };
}

#endif //CHESS_SPOT_H
