//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_ROCK_H
#define CHESS_ROCK_H

#include "Piece.h"

namespace Chess {
class Rock final : public Piece {
public:
    Rock(const bool &side, const Position &pos);

private:
    bool moveStrategy(const Position &nextPos, const Board *board) override;
};
}


#endif //CHESS_ROCK_H
