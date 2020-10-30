//
// Created by Artem Shemidko on 19.10.2020.
//

#include "Board.h"

#include "Spot.h"

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
//        for (int i = 1; i < 7; ++i) {
////            if (i != 4)
//            board[0][i] = std::make_unique<Spot>(Position(0, i));
//        }
        // init spots with white main pieces
        board[0][0] = std::make_unique<Spot>(Position(0, 0), new Rock(ChessSide::WHITE));
        board[0][1] = std::make_unique<Spot>(Position(0, 1), new Knight(ChessSide::WHITE));
        board[0][2] = std::make_unique<Spot>(Position(0, 2), new Bishop(ChessSide::WHITE));
        board[0][3] = std::make_unique<Spot>(Position(0, 3), new Queen(ChessSide::WHITE));
        board[0][4] = std::make_unique<Spot>(Position(0, 4), new King(ChessSide::WHITE));
        board[0][5] = std::make_unique<Spot>(Position(0, 5), new Bishop(ChessSide::WHITE));
        board[0][6] = std::make_unique<Spot>(Position(0, 6), new Knight(ChessSide::WHITE));
        board[0][7] = std::make_unique<Spot>(Position(0, 7), new Rock(ChessSide::WHITE));
        for (int i = 1; i < BOARD_ROWS - 1; ++i) {
            for (int j = 0; j < BOARD_COLS; ++j) {
                if (i == 1 || i == 6) { // for pawns spawn
                    board[i][j] = std::make_unique<Spot>(Position(i, j),
                            new Pawn((i == 1)
                            ? ChessSide::WHITE
                            : ChessSide::BLACK));
                } else { // init void spots on board
                    board[i][j] = std::make_unique<Spot>(Position(i, j));
                }
            }
        }

        // init spots with black main pieces
        board[7][0] = std::make_unique<Spot>(Position (7, 0), new Rock(ChessSide::BLACK));
        board[7][1] = std::make_unique<Spot>(Position (7, 1), new Knight(ChessSide::BLACK));
        board[7][2] = std::make_unique<Spot>(Position (7, 2), new Bishop(ChessSide::BLACK));
        board[7][3] = std::make_unique<Spot>(Position (7, 3), new Queen(ChessSide::BLACK));
        board[7][4] = std::make_unique<Spot>(Position (7, 4), new King(ChessSide::BLACK));
        board[7][5] = std::make_unique<Spot>(Position (7, 5), new Bishop(ChessSide::BLACK));
        board[7][6] = std::make_unique<Spot>(Position (7, 6), new Knight(ChessSide::BLACK));
        board[7][7] = std::make_unique<Spot>(Position (7, 7), new Rock(ChessSide::BLACK));
    }

    void Board::reset() {
        this->initBoard();
    }

    Field<std::unique_ptr<Spot>> &Board::getBoard() {
        return this->board;
    }

    Spot *Board::getSpot(const Position &pos) const {
        return this->board[pos.first][pos.second].get();
    }

    Spot *Board::getSpot(const Types &type, const ChessSide &side) {
        for (const auto &it : board) {
            for (const auto &spot : it) {
                if (auto piece = spot->getPiece()) {
                    if ((piece->getType() == type || type == Types::Any) && piece->getSide() == side) {
                        return spot.get();
                    }
                    else continue;
                }
            }
        }
    }

    std::vector<Spot *> Board::getSpotsByChessSide(const ChessSide &side) {
        std::vector<Spot *> spots;
        for (const auto &it : board) {
            for (const auto &spot : it) {
                if (auto piece = spot->getPiece()) {
                    if (piece->getSide() == side) {
                        spots.push_back(spot.get());
                    }
                    else continue;
                }
            }
        }
        return spots;
    }
}