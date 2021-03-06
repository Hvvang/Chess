//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

namespace Chess {
class Bishop final : public Piece {
public:
    Bishop(const ChessSide &side);

    void name() override { std::cout << (getSide() == ChessSide::WHITE ? "white" : "black") << " bishop" << std::endl; }

private:
    MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_BISHOP_H
