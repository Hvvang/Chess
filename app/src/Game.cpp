//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Game.h"
#include "Board.h"

namespace Chess {
    Game::Game(Players players)
        : board(new Board())
        , move(new Move(board))
        , currTurn(ChessSide::WHITE) {
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
        auto piece = this->board->getSpot(pos)->getPiece();
        if (piece) {
            piece->name();
            if (piece->getSide() == currTurn) {
                return true;
            } else {
                std::cout << "opponent's turn\n";
                return false;
            }
        } else return false;
    }

    Move *Game::getMove() const {
        return move;
    }


}