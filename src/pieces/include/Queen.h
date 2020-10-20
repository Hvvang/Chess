//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

namespace Chess {
    class Queen : public Piece {
    public:
        Queen(const bool &side) : Piece(side) {};
    };
}



#endif //CHESS_QUEEN_H
