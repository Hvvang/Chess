//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Move.h"

namespace Chess {

    Move::Move(Board *board)
        : board(board) {}


//  set current piece to spot that has position = nextPos and
//  remove pointer to current piece in spot that has position = currPos
    void Move::changePosition(const Position &currPos, const Position &nextPos) {
        auto &boardField = board->getField();
        auto piece = boardField[currPos.first][currPos.second]->getPiece();

        boardField[nextPos.first][nextPos.second]->setPiece(piece);
        boardField[currPos.first][currPos.second]->setPiece(nullptr);
    }

    // get moveStatus for current selected piece type
    MoveStatus Move::getMoveStatus(const Position &currPos, const Position &nextPos) const {
        return board->getSpot(currPos)->getPiece()->moveStrategy(currPos, nextPos, board);
    }
}