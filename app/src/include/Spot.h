//
// Created by Artem Shemidko on 27.10.2020.
//

#ifndef CHESS_SPOT_H
#define CHESS_SPOT_H

#include "Piece.h"

namespace Chess {
    using Position = std::pair<int, int>;

    class Piece;
    class Spot {
    public:
        Spot(const Position &pos, Piece *piece = nullptr);
        ~Spot();

        [[nodiscard]] const Position &getPos() const;
        [[nodiscard]] Piece *getPiece() const;
        void setPiece(Piece *piece);
        void pawnPromotion();

    private:
        const Position pos;
        Piece *piece;
    };
}

#endif //CHESS_SPOT_H
