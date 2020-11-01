//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

namespace Chess {
class King final : public Piece {
public:
    King(const ChessSide &side);

    void name() override { std::cout << (getSide() == ChessSide::WHITE ? "white" : "black") << " king" << std::endl; }

    std::vector<Position> getAvailableMoves(const Position &currPos, Board *board) override;

private:
    MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_KING_H
