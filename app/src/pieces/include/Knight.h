//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"

namespace Chess {
class Knight : public Piece {
public:
    Knight(const bool &side, const Position &pos);

private:
    Position getDirection(const Position &currPos, const Position &nextPos) override {return {};};
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_KNIGHT_H
