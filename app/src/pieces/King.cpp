//
// Created by Artem Shemidko on 20.10.2020.
//

#include <cmath>
#include "King.h"

namespace Chess {
    King::King(const ChessSide &side)
            : Piece(side, Types::King) {}

//  available only castle(2step left or right) move and move to nearby spot:
//  if nextPos isn't nearby and it's not a castle move return NotValid move
//  else checking on collision with other pieces
    MoveStatus King::moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) {
        auto deltaY = nextPos.first - currPos.first;
        auto deltaX = nextPos.second - currPos.second;

        // check on king castling
        if ((abs(deltaX) <= 1 && abs(deltaY) <= 1)
            || (!isMoved() && abs(deltaX) == 2 && !abs(deltaY))) {
            auto collision = checkCollision(currPos, nextPos, board);
            if (collision == MoveStatus::Default && abs(deltaX) == 2) {
                return MoveStatus::Castle;
            } else return checkCollision(currPos, nextPos, board);
        } else return MoveStatus::NotValid;
    }

//  returns all available moves for king considering the impossibility of Castling if something wrong:
//      king has moved;
//      rook has moved;
//      isn't rock in the corner.
    std::vector<Position> King::getAvailableMoves(const Position &currPos, Board *board) {
        std::vector<Position> availableMoves;

        for (const auto &spots : board->getField()) {
            for (const auto &it : spots) {
                if (currPos != it->getPos()) {
                    auto moveStatus = moveStrategy(currPos, it->getPos(), board);

                    if (moveStatus != MoveStatus::NotValid) {
                        if (moveStatus == MoveStatus::Castle) {
                            auto rockSpot = board->getSpot(Position(currPos.first, it->getPos().second == 2 ? 0 : 7));
                            auto rockPiece = rockSpot->getPiece();

                            if (rockPiece && rockPiece->getType() == Types::Rock && !rockPiece->isMoved()) {
                                availableMoves.push_back(it->getPos());
                            }
                        } else
                            availableMoves.push_back(it->getPos());
                    }
                }
            }
        }
        return availableMoves;
    }
}
