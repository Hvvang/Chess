//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "Queen.h"

namespace Chess {
    Queen::Queen(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {}

    bool Queen::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();

        if (((currPos.first - nextPos.first) * (currPos.second - nextPos.second))
            || (abs(nextPos.first - currPos.first) != abs(nextPos.second - currPos.second))) {
            return false;
        }
        else return true;
    }
}
