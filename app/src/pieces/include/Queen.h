//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

namespace Chess {
class Queen final : public Piece {
public:
    Queen(const ChessSide &side);

    void name() override { std::cout << (getSide() == ChessSide::WHITE ? "white" : "black") << " queen" << std::endl; }


private:
    MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) override;
};
}



#endif //CHESS_QUEEN_H
