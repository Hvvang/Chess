//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

namespace Chess {
    class Pawn : public Piece {
    public:
        Pawn(const bool &side, std::pair<int, int> pos);

        bool moveStrategy(std::pair<int, int> nextPos) override;
    };
}

#endif //CHESS_PAWN_H
