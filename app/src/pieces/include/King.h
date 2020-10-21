//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

namespace Chess {
class King : public Piece {
public:
    King(const bool &side, const Position &pos);

private:
    Position getDirection(const Position &currPos, const Position &nextPos) override;
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_KING_H
