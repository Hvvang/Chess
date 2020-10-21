//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

namespace Chess {
class Queen : public Piece {
public:
    Queen(const bool &side, const Position &pos);

private:
    Position getDirection(const Position &currPos, const Position &nextPos) override;
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}



#endif //CHESS_QUEEN_H
