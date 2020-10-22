//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

namespace Chess {
class Pawn final : public Piece {
public:
    Pawn(const bool &side, const Position &pos);

private:
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}

#endif //CHESS_PAWN_H
