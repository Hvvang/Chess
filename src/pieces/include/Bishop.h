//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

namespace Chess {
    class Bishop : public Piece {
    public:
        Bishop(const bool &side) : Piece(side) {};
    };
}


#endif //CHESS_BISHOP_H
