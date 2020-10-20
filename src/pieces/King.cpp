//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "King.h"

namespace Chess {
    King::King(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {}

    bool King::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();

        if (abs(nextPos.first - currPos.first) * abs(nextPos.second - currPos.second) <= 1) {
            return true;
        } else return false;
    }
}
