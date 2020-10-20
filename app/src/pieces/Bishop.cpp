//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Bishop.h"

namespace Chess {
    Bishop::Bishop(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {}

    bool Bishop::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();

        if (abs(nextPos.first - currPos.first) == abs(nextPos.second - currPos.second)) {
            return true;
        } else return false;
    }
}
