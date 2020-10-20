//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Board.h"
#include "Piece.h"

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
        board[0][0] = std::make_unique<Spot>(0, 0, new Rock(WHITE, {0, 0}));
        board[0][1] = std::make_unique<Spot>(0, 1, new Knight(WHITE, {0, 1}));
        board[0][2] = std::make_unique<Spot>(0, 2, new Bishop(WHITE, {0, 2}));
        board[0][3] = std::make_unique<Spot>(0, 3, new Queen(WHITE, {0, 3}));
        board[0][4] = std::make_unique<Spot>(0, 4, new King(WHITE, {0, 4}));
        board[0][5] = std::make_unique<Spot>(0, 5, new Bishop(WHITE, {0, 5}));
        board[0][6] = std::make_unique<Spot>(0, 6, new Knight(WHITE, {0, 6}));
        board[0][7] = std::make_unique<Spot>(0, 7, new Rock(WHITE, {0, 7}));

        for (int i = 1; i < BOARD_ROWS - 1; ++i) {
            for (int j = 0; j < BOARD_COLS; ++j) {
                if (i == 1 || i == 7) { // if statement for pawns spawn
                    board[i][j] = std::make_unique<Spot>(i, j, new Pawn((i == 1) ? WHITE : BLACK, {i, j}));
                } else { // init void spots on board
                    board[i][j] = std::make_unique<Spot>(i, j);
                }
            }
        }

        // init spots with black main pieces
        board[7][0] = std::make_unique<Spot>(7, 0, new Rock(BLACK, {7, 0}));
        board[7][1] = std::make_unique<Spot>(7, 1, new Knight(BLACK, {7, 1}));
        board[7][2] = std::make_unique<Spot>(7, 2, new Bishop(BLACK, {7, 2}));
        board[7][3] = std::make_unique<Spot>(7, 3, new Queen(BLACK, {7, 3}));
        board[7][4] = std::make_unique<Spot>(7, 4, new King(BLACK, {7, 4}));
        board[7][5] = std::make_unique<Spot>(7, 5, new Bishop(BLACK, {7, 5}));
        board[7][6] = std::make_unique<Spot>(7, 6, new Knight(BLACK, {7, 6}));
        board[7][7] = std::make_unique<Spot>(7, 7, new Rock(BLACK, {7, 7}));
    }

    void Board::update() {

    }

}