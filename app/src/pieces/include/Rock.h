//
// Created by Artem Shemidko on 22.10.2020.
//

#ifndef CHESS_ROCK_H
#define CHESS_ROCK_H

#include "Piece.h"

namespace Chess {
class Rock : public Piece {
public:
    Rock(const ChessSide &side, const Position &pos);
    ~Rock() = default;

private:
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_ROCK_H
