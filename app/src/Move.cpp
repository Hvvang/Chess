//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Move.h"
#include <iostream>

namespace Chess {

    Move::Move(Board *board)
        : board(board) {}

    void Move::changePosition(const Position &currPos, const Position &nextPos) {
        auto currPiece = board->getSpot(currPos);
        auto nextPiece = board->getSpot(nextPos);

        if (currPiece->canMove(nextPos, board)) {
                auto &boardField = board->getBoard();
                if (nextPiece) {
                    boardField[nextPos.first][nextPos.second].reset();
                }
                boardField[currPos.first][currPos.second].swap(boardField[nextPos.first][nextPos.second]);
                boardField[nextPos.first][nextPos.second]->setPosition(nextPos);
        }
    }
}