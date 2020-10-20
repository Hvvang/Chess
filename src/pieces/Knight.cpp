//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Knight.h"

namespace Chess {
    Knight::Knight(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {}

    bool Knight::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();

        if ((abs(nextPos.first - currPos.first) == 2 && abs(nextPos.second - currPos.second) == 1)
            || (abs(nextPos.first - currPos.first) == 1 && abs(nextPos.second - currPos.second) == 2)) {
            return true;
        } else return false;
    }
}
