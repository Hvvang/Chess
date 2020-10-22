//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H
#include "Piece.h"
#include <string>

namespace Chess {
    class Player {
    public:
        Player(const ChessSide &side = ChessSide::WHITE, const std::string &userName = "Player1");
        virtual ~Player() = default;

        const std::string &getName() const;
        const ChessSide &getSide() const;

    private:
        ChessSide side;
        std::string userName;
    };
}


#endif //CHESS_PLAYER_H
