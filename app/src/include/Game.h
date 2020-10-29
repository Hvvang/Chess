//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <utility>
#include "Player.h"
#include "Move.h"

namespace Chess {
    enum class GameStatus {
        Default,
        KingCheck,
        PawnPromotion,

    };

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
        bool isCheck(const Position &kingPos);
        bool isCheckmate();
        void run();
        const bool &isCurrTurn(const Position &pos);

    private:
        void changeTurn();
        void addMoveToHistory(const std::pair<Position, Position> &move);

    private:
        Players players;
        ChessSide currTurn;
        Board *board;
        Move *move;
        std::vector<std::pair<Position, Position>> movesHistory;
    };
}


#endif //CHESS_GAME_H
