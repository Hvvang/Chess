//
// Created by Artem Shemidko on 20.10.2020.
//

#include "King.h"

namespace Chess {
    King::King(const bool &side, std::pair<int, int> pos)
            : Piece(side, pos) {}

    bool King::moveStrategy(std::pair<int, int> nextPos) {

    }
}
