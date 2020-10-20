//
// Created by Artem Shemidko on 20.10.2020.
//

#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

namespace Chess {
    class King : public Piece {
    public:
        King(const bool &side, std::pair<int, int> pos);

        bool moveStrategy(std::pair<int, int> nextPos) override;
    };
}


#endif //CHESS_KING_H
