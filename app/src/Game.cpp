//
// Created by Artem Shemidko on 19.10.2020.
//

#include <Pawn.h>
#include <King.h>
#include <Queen.h>
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
        if (auto piece = board->getSpot(pos)->getPiece(); piece) {
            return piece->getSide() == currTurn ? true : false;
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
            it->getPiece()->name();
            if (move->getMoveStatus(it->getPos(), kingPos) != MoveStatus::NotValid
                && it->getPos() != kingPos) {
//                std::cout << "Check" << std::endl;
                return true;
            }
//            std::cout << "not Check" << std::endl;
        }
        return false;
    }

    bool Game::isCheck(const Position &kingPos, const Position &nextPos) {
        auto opponentSide = (currTurn == ChessSide::WHITE) ? ChessSide::BLACK : ChessSide::WHITE;
        auto opponentPieces = board->getSpotsByChessSide(opponentSide);
        auto pieceInNextPos = board->getSpot(nextPos)->getPiece();

        board->getSpot(nextPos)->setPiece(new Pawn(currTurn));
        for (const auto &it : opponentPieces) {
            if (it->getPiece()->canMove(it->getPos(), kingPos, board) != MoveStatus::NotValid
                && it->getPos() != kingPos) {
//                std::cout << "Check" << std::endl;
                board->getSpot(nextPos)->setPiece(pieceInNextPos);
                return true;
            }
//            std::cout << "not Check" << std::endl;
        }
        board->getSpot(nextPos)->setPiece(pieceInNextPos);
        return false;
    }

    void Game::changeTurn()  {
        this->currTurn = (this->currTurn == ChessSide::WHITE) ? ChessSide::BLACK : ChessSide::WHITE;
    }

    void Game::addMoveToHistory(const std::pair<Position, Position> &movePosition) {
        movesHistory.push_back(movePosition);
    }

    bool Game::isCheckmate() {
        auto currKing = board->getSpot(Chess::Types::King, currTurn);
        auto currPos = currKing->getPos();
        auto pos = currKing->getPiece()->getAvailibleMoves(currKing->getPos(), board);

        // isn`t checkmate if king has a move
        for (const auto &it : pos) {
            move->changePosition(currKing->getPos(), it);
            if (!isCheck(it)) {
                move->changePosition(it, currKing->getPos());
//                currKing->setPiece(kingPiece);
                return false;
            }
            move->changePosition(it, currKing->getPos());
        }
        auto currPieces = board->getSpotsByChessSide(currTurn);
        for (const auto & spot : currPieces) {
            if (spot != currKing) {
                pos = spot->getPiece()->getAvailibleMoves(spot->getPos(), board);
                for (const auto &it : pos) {
                    if (!isCheck(currKing->getPos(), it))
                        return false;
                }
            }
        }
        return true;
    }

    const GameStatus &Game::makeMove(const Position &currPos, const Position &nextPos) {
        if (currPos != nextPos) {
            if (auto moveStatus = move->getMoveStatus(currPos, nextPos); moveStatus != MoveStatus::NotValid) {
                if (moveStatus == MoveStatus::Default || moveStatus == MoveStatus::KillMove) {
                    auto pieceInNextPos = board->getSpot(nextPos)->getPiece();
                    move->changePosition(currPos, nextPos);
                    if (auto kingPos = board->getSpot(Types::King, currTurn)->getPos(); isCheck(kingPos)) {
                        move->changePosition(nextPos, currPos);
                        board->getSpot(nextPos)->setPiece(pieceInNextPos);
                        if (isCheckmate()) {
                            return isCheck(kingPos) ? GameStatus::KingCheckMate : GameStatus::KingStaleMate;
                        }
                        return GameStatus::KingCheck;
                    }
                    board->getSpot(nextPos)->getPiece()->setHasMoved();
                    changeTurn();
                    return GameStatus::Default;
                }
                else if (moveStatus == MoveStatus::Castle) {
                    auto rockSpot = board->getSpot(Position(currPos.first, nextPos.second == 2 ? 0 : 7));
                    auto rockPiece = rockSpot->getPiece();

                    if (rockPiece && rockPiece->getType() == Types::Rock && !rockPiece->isHasMoved()) {
                        auto rockPosAfterCastling = Position(currPos.first, nextPos.second == 2 ? 3 : 5);

                        if (isCheck(currPos) || isCheck(rockPosAfterCastling) || isCheck(nextPos)) {
                            if (isCheckmate()) {
                                return GameStatus::KingCheckMate;
                            }
                            return GameStatus::InvalidCastle;
                        }
                        move->changePosition(currPos, nextPos);
                        move->changePosition(rockSpot->getPos(), rockPosAfterCastling);
                        rockPiece->setHasMoved();
                        board->getSpot(nextPos)->getPiece()->setHasMoved();
                        changeTurn();
                        if (isCheckmate())
                            return GameStatus::KingCheckMate;
                        return GameStatus::Castle;
                    } else return GameStatus::InvalidCastle;
                }
                else if (moveStatus == MoveStatus::PawnPromotion) {
                    move->changePosition(currPos, nextPos);
                    if (auto kingPos = board->getSpot(Types::King, currTurn); isCheck(kingPos->getPos())) {
                        move->changePosition(nextPos, currPos);
                        if (isCheckmate()) {
                            return GameStatus::KingCheckMate;
                        }
                        return GameStatus::KingCheck;
                    }
//                    board->getSpot(nextPos)->pawnPromotion();
                    board->getSpot(nextPos)->setPiece(new Queen(currTurn));
                    board->getSpot(nextPos)->getPiece()->setHasMoved();
                    changeTurn();
                    if (isCheckmate()) {
                        return GameStatus::KingCheckMate;
                    }
                    return GameStatus::Default;
                }
            } else return GameStatus::InvalidMove;
        } else return GameStatus::DoesntMove;
    }
}
