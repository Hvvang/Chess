//
// Created by Artem Shemidko on 20.10.2020.
//

#include "Rock.h"


namespace Chess {
    Rock::Rock(const bool &side, std::pair<int, int> pos)
        : Piece(side, pos) {}

    bool Rock::moveStrategy(std::pair<int, int> nextPos) {
        auto currPos = getPosition();

        if ((currPos.first - nextPos.first) * (currPos.second - nextPos.second))
            return false;
        else
            return true;
    }
}


