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
        this->currTurn = ChessSide::WHITE;
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

    // getting current player king layout and checking it collision with opponents` pieces
    bool Game::isCheck(const Position &kingPos) {
        auto opponentSide = (currTurn == ChessSide::WHITE) ? ChessSide::BLACK : ChessSide::WHITE;
        auto opponentPieces = board->getSpotsByChessSide(opponentSide);

        for (const auto &it : opponentPieces) {
            if (it->getPiece()->canMove(it->getPos(), kingPos, board) == MoveStatus::KillMove
                && it->getPos() != kingPos) {
                std::cout << "Check" << std::endl;
                return true;
            }
            std::cout << "not Check" << std::endl;
        }
        return false;
    }



    void Game::changeTurn() {
        this->currTurn = (this->currTurn == ChessSide::WHITE) ? ChessSide::BLACK : ChessSide::WHITE;
    }

    void Game::addMoveToHistory(const std::pair<Position, Position> &move) {
        movesHistory.push_back(move);
    }

    bool Game::isCheckmate() {
        auto currKing = board->getSpot(Chess::Types::King, currTurn);
        auto pos = currKing->getPiece()->getAvailibleMoves(currKing->getPos(), board);

        for (const auto &it : pos) {
            if (!isCheck(it))
                return false;
        }

        auto currPieces = board->getSpotsByChessSide(currTurn);
        for (const auto & piece : currPieces) {
            pos = currKing->getPiece()->getAvailibleMoves(currKing->getPos(), board);
            for (const auto &it : pos) {
                if (!isCheck(it))
                    return false;
            }
        }


        return true;
    }


}