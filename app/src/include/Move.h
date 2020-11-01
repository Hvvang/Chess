//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "Board.h"
#include "Piece.h"
#include "Player.h"

namespace Chess {
    class Move {
    public:
        Move(Board *board);
        ~Move() = default;

        MoveStatus getMoveStatus(const Position &currPos, const Position &nextPos) const;

        void changePosition(const Position &currPos, const Position &nextPos);

    private:

        Board *board;
    };
}


#endif //CHESS_MOVE_H
