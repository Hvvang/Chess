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

//  TODO: add unit_tests for checking different pieces moveStrategy

namespace Chess {

    Board::Board() {
        initBoard();
    }

    void Board::initBoard() {
//        for (int i = 0; i < 8; ++i) {
//            for (int j = 0; j < 8; j++) {
//                field[i][j] = std::make_unique<Spot>(Position(i, j));
//            }
//        }
        // init spots with white main pieces
        field[0][0] = std::make_unique<Spot>(Position(0, 0), new Rock(ChessSide::WHITE));
        field[0][1] = std::make_unique<Spot>(Position(0, 1), new Knight(ChessSide::WHITE));
        field[0][2] = std::make_unique<Spot>(Position(0, 2), new Bishop(ChessSide::WHITE));
        field[0][3] = std::make_unique<Spot>(Position(0, 3), new Queen(ChessSide::WHITE));
        field[0][4] = std::make_unique<Spot>(Position(0, 4), new King(ChessSide::WHITE));
        field[0][5] = std::make_unique<Spot>(Position(0, 5), new Bishop(ChessSide::WHITE));
        field[0][6] = std::make_unique<Spot>(Position(0, 6), new Knight(ChessSide::WHITE));
        field[0][7] = std::make_unique<Spot>(Position(0, 7), new Rock(ChessSide::WHITE));
        for (int i = 1; i < BOARD_ROWS - 1; ++i) {
            for (int j = 0; j < BOARD_COLS; ++j) {
                if (i == 1 || i == 6) { // for pawns spawn
                    field[i][j] = std::make_unique<Spot>(Position(i, j),
                            new Pawn((i == 1)
                            ? ChessSide::WHITE
                            : ChessSide::BLACK));
                } else { // init void spots on field
                    field[i][j] = std::make_unique<Spot>(Position(i, j));
                }
            }
        }

        // init spots with black main pieces
        field[7][0] = std::make_unique<Spot>(Position (7, 0), new Rock(ChessSide::BLACK));
        field[7][1] = std::make_unique<Spot>(Position (7, 1), new Knight(ChessSide::BLACK));
        field[7][2] = std::make_unique<Spot>(Position (7, 2), new Bishop(ChessSide::BLACK));
        field[7][3] = std::make_unique<Spot>(Position (7, 3), new Queen(ChessSide::BLACK));
        field[7][4] = std::make_unique<Spot>(Position (7, 4), new King(ChessSide::BLACK));
        field[7][5] = std::make_unique<Spot>(Position (7, 5), new Bishop(ChessSide::BLACK));
        field[7][6] = std::make_unique<Spot>(Position (7, 6), new Knight(ChessSide::BLACK));
        field[7][7] = std::make_unique<Spot>(Position (7, 7), new Rock(ChessSide::BLACK));
    }

    void Board::reset() {
        this->initBoard();
    }

    Field<std::unique_ptr<Spot>> &Board::getField() {
        return this->field;
    }

//  returns Spot that situated in the pos
    Spot *Board::getSpot(const Position &pos) const {
        return this->field[pos.first][pos.second].get();
    }

//  returns Spot that contains pieces of chess Type = type and chessSide = side
//  or nullptr if not found
    Spot *Board::getSpot(const Types &type, const ChessSide &side) {
        for (const auto &it : field) {
            for (const auto &spot : it) {
                if (auto piece = spot->getPiece()) {
                    if ((piece->getType() == type || type == Types::Any) && piece->getSide() == side) {
                        return spot.get();
                    }
                    else continue;
                }
            }
        }
        return nullptr;
    }

//  returns a vector of all found Spot that contains pieces of chessSide = side
    std::vector<Spot *> Board::getSpotsByChessSide(const ChessSide &side) {
        std::vector<Spot *> spots;
        for (const auto &it : field) {
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