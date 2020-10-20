//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Pawn.h"

namespace Chess {
    Pawn::Pawn(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {};

    // check on changing pawn row position depended on color of piece
    int checkForwardMove(const int &currRow, const int &nextRow, const bool &side) {
        // allow only forward moving
        if ((nextRow > currRow && side)
            || (nextRow < currRow && !side)) {
            // allow move through two spot only on own side
            if ((side && nextRow > 3) || (!side && nextRow < 4)) {
                if (abs(nextRow - currRow) == 1)
                    return 1;
                else return false;
            } else if ((side && nextRow < 4) || (!side && nextRow > 3)) {
                return abs(nextRow - currRow);
            }
        } else return 0;
    }

    bool Pawn::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();
        auto forwardMove = checkForwardMove(currPos.second, nextPos.second, getSide());
        auto diagonalMove = abs(currPos.first - nextPos.first);

        if (diagonalMove == 1 && forwardMove == 1) {
            return abs(currPos.first - nextPos.first);
        } else if (diagonalMove == 0 && forwardMove != 0) {
            return true;
        } else return false;
    }
}