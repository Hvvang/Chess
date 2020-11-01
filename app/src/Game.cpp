//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Game.h"
#include "Board.h"

namespace Chess {
    Game::Game(Players players)
        : board(new Board())
        , move(new Move(board)) {
        this->currTurn = ChessSide::WHITE;
        this->players = std::move(players);
        this->board->initBoard();
    }

    Game::~Game() {
        delete board;
        delete move;
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

    void Game::setBoard(Board *boardObj) {
        this->board = boardObj;
    }

    Move *Game::getMove() const {
        return move;
    }

//  reset all data to start new game
    void Game::reset() {
        currTurn = ChessSide::WHITE;
        currPieceSpot = nullptr;
        board->reset();
        movesHistory.clear();
    }

    void Game::changeTurn()  {
        currTurn = static_cast<ChessSide>(!static_cast<int>(currTurn));
    }

//  return true if the piece that situated in the pos is belong to player that has currTurn
//  return false on another side or if any piece does`t situated in the pos
    bool Game::isCurrPlayerPiece(const Position &pos) {
        auto piece = board->getSpot(pos)->getPiece();
        return piece && piece->getSide() == currTurn;
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
//            it->getPiece()->name();
//            std::cout << it->getPos().second << " " << it->getPos().first << std::endl;

            if (move->getMoveStatus(it->getPos(), kingPos) != MoveStatus::NotValid
                && it->getPos() != kingPos) {
                return true;
            }
        }
//        std::cout << "go back\n";
        return false;
    }

    void Game::addMoveToHistory(const std::pair<Position, Position> &movePosition) {
        std::string translate_from(1, toascii(movePosition.first.second + 'A'));
        std::string translate_to(1, toascii(movePosition.second.second + 'A'));
        translate_from += std::to_string(movePosition.first.first);
        translate_to += std::to_string(movePosition.second.first);

        movesHistory.push_back(translate_from + " " + translate_to);
    }

    bool Game::isCheckmate() {
        auto currKing = board->getSpot(Chess::Types::King, currTurn);
        auto currKingPos = currKing->getPos();
        auto pos = currKing->getPiece()->getAvailableMoves(currKing->getPos(), board);

        // isn`t checkmate if king has a available movement
        for (const auto &it : pos) {
            auto pieceInNextPos = board->getSpot(it)->getPiece();
            move->changePosition(currKingPos, it);
            auto checkStatus = isCheck(it);
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
    GameStatus Game::makeMove(const Position &toPos) {
        auto spot = board->getSpot(toPos);

        if (!currPieceSpot && spot->getPiece()) {
            if (isCurrPlayerPiece(toPos)) {
                currPieceSpot = spot;
                return GameStatus::PieceSelected;
            } else
                return GameStatus::PieceAnotherPlayer;
        } else if (!currPieceSpot && !spot->getPiece())
            return GameStatus::PieceNotSelected;

        auto currPos = currPieceSpot->getPos();
        if (currPieceSpot->getPos() == toPos) {
            currPieceSpot = nullptr;
            return GameStatus::PieceUnSelected;
        }

        auto moveStatus = move->getMoveStatus(currPos, toPos);
        if (moveStatus != MoveStatus::NotValid) {
            auto status = GameStatus::Default;
            auto pieceInNextPos = spot->getPiece();

            move->changePosition(currPos, toPos);
            if (isCheck())
                status = GameStatus::KingCheck;

            if (moveStatus == MoveStatus::Castle) {
                if (status == GameStatus::KingCheck) {
                    status = GameStatus::InvalidCastle;
                } else {
                    auto rockSpot = board->getSpot(Position(currPos.first, toPos.second == 2 ? 0 : 7));
                    auto rockPiece = rockSpot->getPiece();

                    if (rockPiece && rockPiece->getType() == Types::Rock && !rockPiece->isMoved()) {
                        auto rockPosAfterCastling = Position(currPos.first, toPos.second == 2 ? 3 : 5);

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
            } else if (moveStatus == MoveStatus::PawnPromotion && status != GameStatus::KingCheck) {
                board->getSpot(toPos)->pawnPromotion();
            }

            if (status == GameStatus::KingCheck || status == GameStatus::InvalidCastle) {
                move->changePosition(toPos, currPos);
                board->getSpot(toPos)->setPiece(pieceInNextPos);
            } else {
                board->getSpot(toPos)->getPiece()->setHasMoved();
                addMoveToHistory({currPos, toPos});
                changeTurn();
            }
            currPieceSpot = nullptr;
            return status;
        } else {
            currPieceSpot = nullptr;
            return GameStatus::InvalidMove;
        }
    }

    GameStatus Game::getCheckStatus()  {
        auto checkStatus = isCheck();
        auto checkmateStatus = isCheckmate();

        if (checkStatus && !checkmateStatus) {
            return GameStatus::KingCheck;
        } else if (!checkStatus && checkmateStatus) {
            return GameStatus::KingStaleMate;
        } else if (checkStatus) {
            return GameStatus::KingCheckMate;
        } else {
            return GameStatus::Default;
        }
    }

    const Player &Game::getCurrPlayer() const {
        return (players.first.getSide() == currTurn) ? players.first : players.second;
    }
    const std::vector<std::string> &Game::getMovesHistory() const {
        return movesHistory;
    }
}
