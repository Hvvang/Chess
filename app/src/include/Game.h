//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <utility>
#include "Player.h"
#include "Move.h"

namespace Chess {
    using Players = std::pair<Player, Player>;

    class Game {
    public:
        Game(Players players);
        ~Game() = default;

        [[nodiscard]] const Players &getPlayers() const;
        [[nodiscard]] Board *getBoard() const;
        [[nodiscard]] const ChessSide &getCurrTurn() const;
        [[nodiscard]] Move *getMove() const;

        void setBoard(Board *board);
        bool isCheck();
        void run();
        const bool &isCurrTurn(const Position &pos);

    private:
        void changeTurn();

    private:
        Players players;
        ChessSide currTurn;
        Board *board;
        Move *move;

    };
}


#endif //CHESS_GAME_H
