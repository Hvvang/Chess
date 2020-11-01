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
        KingCheckMate,
        KingStaleMate,
        InvalidMove,
        Castle,
        InvalidCastle,
        PieceAnotherPlayer,
        PieceSelected,
        PieceUnSelected,
        PieceNotSelected
};

    using Players = std::pair<Player, Player>;

    class Game {
    public:
        Game(Players players);
        ~Game() = default;

        [[nodiscard]] const Players &getPlayers() const;
        [[nodiscard]] const Player &getCurrPlayer() const;
        [[nodiscard]] Board *getBoard() const;
        [[nodiscard]] const ChessSide &getCurrTurn() const;
        [[nodiscard]] Move *getMove() const;

        void setBoard(Board *board);
        void reset();
        bool isCurrPlayerPiece(const Position &pos);

        GameStatus makeMove(const Position &toPos);
        GameStatus getCheckStatus();
        const std::vector<std::string> &getMovesHistory() const;

    private:
        bool isCheckmate();
        bool isCheck();
        bool isCheck(const Position &kingPos);
        void changeTurn();
        void addMoveToHistory(const std::pair<Position, Position> &move);

    private:
        Players players;
        ChessSide currTurn = ChessSide::WHITE;
        Spot *currPieceSpot = nullptr;
        Board *board;
        Move *move;
        std::vector<std::string> movesHistory;


    };
}


#endif //CHESS_GAME_H
