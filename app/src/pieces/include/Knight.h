//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"

namespace Chess {
class Knight final : public Piece {
public:
    Knight(const ChessSide &side);


private:
    MoveStatus checkCollision(const Position &currPos, const Position &nextPos, const Board *board) override;
    MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_KNIGHT_H
