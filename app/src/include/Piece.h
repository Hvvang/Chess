//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <utility>
#include "Board.h"
#include <iostream>
#include "Spot.h"

namespace Chess {
    using Position = std::pair<int, int>;

    enum class ChessSide {
        WHITE,
        BLACK
    };

    enum class MoveStatus {
        Default,
        Castle,
        PawnPromotion,
        KillMove,
        NotValid
    };

    class Board;
    class Piece {
    public:
        Piece(const ChessSide &side = ChessSide::WHITE);

        [[nodiscard]] const ChessSide &getSide() const;
        [[nodiscard]] const bool &isKilled() const;

        void setDeath(const bool &death = true);

        virtual MoveStatus canMove(const Position &currPos, const Position &nextPos, Board *board);

    protected:
        virtual MoveStatus checkCollision(const Position &currPos, const Position &nextPos, const Board *board);

    private:
        Position getDirection(const int &deltaX, const int &deltaY);
        virtual MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) = 0;

    private:
        const ChessSide side;
        bool death = false;
    };
}

#endif //CHESS_PIECE_H
