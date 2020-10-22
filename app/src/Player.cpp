//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Player.h"

namespace Chess {

    Player::Player(const ChessSide &side, const std::string &userName)
        : side(side)
        , userName(userName) {}

    const std::string &Player::getName() const {
        return userName;
    }

    const ChessSide &Player::getSide() const {
        return side;
    };
}