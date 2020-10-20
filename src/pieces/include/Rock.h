//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_ROCK_H
#define CHESS_ROCK_H

#include "Piece.h"

namespace Chess {
class Rock : public Piece {
    public:
        Rock(const bool &side) : Piece(side) {};
    };
}


#endif //CHESS_ROCK_H
