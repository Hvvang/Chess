//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Game.h"
#include "Board.h"

namespace Chess {
    Game::Game(Players players)
        : board(new Board())
        , move(new Move(board))
        , currTurn(ChessSide::BLACK) {
        this->players = std::move(players);
        this->board->initBoard();
    }

    const Players &Game::getPlayers() const {
        return players;
    }

    Board *Game::getBoard() const {
        return board;
    }

    const ChessSide &Game::getCurrTurn() const {
        return currTurn;
    }

    void Game::setCurrTurn(const ChessSide &currTurn) {
        this->currTurn = currTurn;
    }

    void Game::setBoard(Board *board) {
        this->board = board;
    }

    void Game::run() {
    }

    const bool &Game::isCurrTurn(const Position &pos) {
        if (auto piece = this->board->getSpot(pos)) {
            std::cout << "34\n";
//            auto t = piece->getSide();
//            std::cout << "343\n";
//            if (piece->getSide() == currTurn) {
//                std::cout << "35\n";
//
                return true;
//            }
        } else return false;
    }

    Move *Game::getMove() const {
        return move;
    }


}