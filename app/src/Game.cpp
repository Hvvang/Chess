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

    Move *Game::getMove() const {
        return move;
    }

    void Game::run() {
    }

    void Game::changeTurn()  {
        currTurn = static_cast<ChessSide>(!static_cast<int>(currTurn));
    }

    //  return true if the piece that situated in the pos is belong to player that has currTurn
//  return false on another side or if any piece does`t situated in the pos
    const bool &Game::isCurrTurn(const Position &pos) {
        if (auto piece = board->getSpot(pos)->getPiece(); piece) {
            return piece->getSide() == currTurn ? true : false;
        } else return false;
    }

    bool Game::isCheck() {
        auto kingPos = board->getSpot(Types::King, currTurn)->getPos();
        return isCheck(kingPos);
    }

//  getting current player king layout and checking it collision with opponents` pieces
//  if collision exist function return true and that means current player has a KingChecking
    bool Game::isCheck(const Position &kingPos) {
        auto opponentSide = (currTurn == ChessSide::WHITE) ? ChessSide::BLACK : ChessSide::WHITE;
        auto opponentPieces = board->getSpotsByChessSide(opponentSide);

        for (const auto &it : opponentPieces) {
            if (move->getMoveStatus(it->getPos(), kingPos) != MoveStatus::NotValid
                && it->getPos() != kingPos) {
                return true;
            }
        }
        return false;
    }

    void Game::addMoveToHistory(const std::pair<Position, Position> &movePosition) {
        movesHistory.push_back(movePosition);
    }

    bool Game::isCheckmate() {
        auto currKing = board->getSpot(Chess::Types::King, currTurn);
        auto currKingPos = currKing->getPos();
        auto pos = currKing->getPiece()->getAvailableMoves(currKing->getPos(), board);

        // isn`t checkmate if king has a available movement
        for (const auto &it : pos) {
            auto pieceInNextPos = board->getSpot(it)->getPiece();
            move->changePosition(currKingPos, it);
            auto checkStatus = isCheck(currKingPos);
            move->changePosition(it, currKingPos);
            board->getSpot(it)->setPiece(pieceInNextPos);
            if (!checkStatus) {
                return false;
            } else continue;
        }

//      checking on allied pieces to defend against KingChecking
//      receive availablePoses to move for every allied pieces
//      and check all of them on defending in func isCheck
        auto currPieces = board->getSpotsByChessSide(currTurn);
        for (const auto & spot : currPieces) {
            if (spot != currKing) {
                pos = spot->getPiece()->getAvailableMoves(spot->getPos(), board);
                for (const auto &it : pos) {
                    auto pieceInNextPos = board->getSpot(it)->getPiece();
                    move->changePosition(spot->getPos(), it);
                    auto checkStatus = isCheck();
                    move->changePosition(it, spot->getPos());
                    board->getSpot(it)->setPiece(pieceInNextPos);
                    if (!checkStatus) {
                        return false;
                    } else continue;
                }
            }
        }
        return true;
    }

//  Function returns different GameStatuses dependent on Poses and make pieces change position
//  if it's possible dependent on moveStrategy, kingChecking, and etc.
//  TODO: add game status and movement log;
//        (optional) adding move history and then implementation of redo/undo funcs;
    const GameStatus Game::makeMove(const Position &currPos, const Position &nextPos) {
        if (currPos != nextPos) {
            if (auto moveStatus = move->getMoveStatus(currPos, nextPos); moveStatus != MoveStatus::NotValid) {
                auto status = GameStatus::Default;
                auto pieceInNextPos = board->getSpot(nextPos)->getPiece();
                move->changePosition(currPos, nextPos);

                if (isCheck()) {
                    status = GameStatus::KingCheck;
                }

                if (moveStatus == MoveStatus::Castle && status != GameStatus::KingCheck) {
                    auto rockSpot = board->getSpot(Position(currPos.first, nextPos.second == 2 ? 0 : 7));
                    auto rockPiece = rockSpot->getPiece();

                    if (rockPiece && rockPiece->getType() == Types::Rock && !rockPiece->isMoved()) {
                        auto rockPosAfterCastling = Position(currPos.first, nextPos.second == 2 ? 3 : 5);

                        if (isCheck(currPos) || isCheck(rockPosAfterCastling)) {
                            status = GameStatus::InvalidCastle;
                        } else {
                            move->changePosition(rockSpot->getPos(), rockPosAfterCastling);
                            rockPiece->setHasMoved();
                            status = GameStatus::Castle;
                        }
                    } else {
                        status = GameStatus::InvalidCastle;
                    }
                }

                else if (moveStatus == MoveStatus::PawnPromotion && status != GameStatus::KingCheck) {
                    board->getSpot(nextPos)->pawnPromotion();
                }

                if (status == GameStatus::KingCheck || status == GameStatus::InvalidCastle) {
                    move->changePosition(nextPos, currPos);
                    board->getSpot(nextPos)->setPiece(pieceInNextPos);
                } else {
                    board->getSpot(nextPos)->getPiece()->setHasMoved();
                    changeTurn();
                }
                return status;
            } else return GameStatus::InvalidMove;
        } else return GameStatus::DoesntMove;
    }

    GameStatus Game::getCheckStatus()  {
        auto checkStatus = isCheck();
        auto checkmateStatus = isCheckmate();

        if (checkStatus && !checkmateStatus) {
            return GameStatus::KingCheck;
        } else if (!checkStatus && checkmateStatus) {
            return GameStatus::KingStaleMate;
        } else if (checkStatus && checkmateStatus) {
            return GameStatus::KingCheckMate;
        } else {
            return GameStatus::Default;
        }
    }

    const Player &Game::getCurrPlayer() const {
        return (players.first.getSide() == currTurn) ? players.first : players.second;
    }
}
