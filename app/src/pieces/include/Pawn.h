//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

namespace Chess {
class Pawn : public Piece {
public:
    Pawn(const bool &side, const Position &pos);

private:
    Position getDirection(const Position &currPos, const Position &nextPos) override;
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}

#endif //CHESS_PAWN_H
