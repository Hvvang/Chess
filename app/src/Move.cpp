//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Move.h"
#include <iostream>

namespace Chess {

    Move::Move(Board *board)
        : board(board) {}

    void Move::changePosition(const Position &currPos, const Position &nextPos) {
        auto currPiece = board->getSpot(currPos)->getPiece();
        auto nextPiece = board->getSpot(nextPos)->getPiece();

        if (currPiece->canMove(currPos, nextPos, board) != MoveStatus::NotValid) {
            auto &boardField = board->getBoard();
            if (nextPiece) {
                boardField[nextPos.first][nextPos.second].reset();
            }
            boardField[nextPos.first][nextPos.second]->setPiece(boardField[currPos.first][currPos.second]->getPiece());
            boardField[currPos.first][currPos.second]->setPiece(nullptr);
//            boardField[currPos.first][currPos.second].swap(boardField[nextPos.first][nextPos.second]);
//            boardField[nextPos.first][nextPos.second]->setPosition(nextPos);
        } else {
            std::cout << "not valid" << std::endl;
        }
    }

    MoveStatus Move::getMoveStatus(const Position &currPos, const Position &nextPos) {
        return board->getSpot(currPos)->getPiece()->canMove(currPos, nextPos, board);
    }
}