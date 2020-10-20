//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"

namespace Chess {
class Knight : public Piece {
    public:
    Knight(const bool &side, std::pair<int, int> pos);

    bool moveStrategy(std::pair<int, int> nextPos) override;
    };
}


#endif //CHESS_KNIGHT_H
