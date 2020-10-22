//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Board.h"

#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rock.h"

namespace Chess {

    Board::Board() {
        initBoard();
    }

    void Board::initBoard() {
        // init spots with white main pieces
        board[0][0] = std::make_unique<Piece>(Rock(ChessSide::WHITE, {0, 1}));
        board[0][1] = std::make_unique<Piece>(Knight(ChessSide::WHITE, {0, 1}));
        board[0][2] = std::make_unique<Piece>(Bishop(ChessSide::WHITE, {0, 2}));
        board[0][3] = std::make_unique<Piece>(Queen(ChessSide::WHITE, {0, 3}));
        board[0][4] = std::make_unique<Piece>(King(ChessSide::WHITE, {0, 4}));
        board[0][5] = std::make_unique<Piece>(Bishop(ChessSide::WHITE, {0, 5}));
        board[0][6] = std::make_unique<Piece>(Knight(ChessSide::WHITE, {0, 6}));
        board[0][7] = std::make_unique<Piece>(Rock(ChessSide::WHITE, {0, 7}));

        for (int i = 1; i < BOARD_ROWS - 1; ++i) {
            for (int j = 0; j < BOARD_COLS; ++j) {
                if (i == 1 || i == 6) { // for pawns spawn
                    board[i][j] = std::make_unique<Piece>(Pawn((i == 1)
                            ? ChessSide::WHITE
                            : ChessSide::BLACK
                            , {i, j}));
                } else { // init void spots on board
                    board[i][j] = std::make_unique<Piece>();
                }
            }
        }

        // init spots with black main pieces
        board[7][0] = std::make_unique<Piece>(Rock(ChessSide::BLACK, {7, 0}));
        board[7][1] = std::make_unique<Piece>(Knight(ChessSide::BLACK, {7, 1}));
        board[7][2] = std::make_unique<Piece>(Bishop(ChessSide::BLACK, {7, 2}));
        board[7][3] = std::make_unique<Piece>(Queen(ChessSide::BLACK, {7, 3}));
        board[7][4] = std::make_unique<Piece>(King(ChessSide::BLACK, {7, 4}));
        board[7][5] = std::make_unique<Piece>(Bishop(ChessSide::BLACK, {7, 5}));
        board[7][6] = std::make_unique<Piece>(Knight(ChessSide::BLACK, {7, 6}));
        board[7][7] = std::make_unique<Piece>(Rock(ChessSide::BLACK, {7, 7}));
    }

    void Board::reset() {
        this->initBoard();
    }

    Field<std::unique_ptr<Piece>> &Board::getBoard() {
        return this->board;
    }

    Piece *Board::getSpot(const Position &pos) const {
        return this->board[pos.first][pos.second].get();
    }
}