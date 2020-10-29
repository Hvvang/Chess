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
        WHITE = 0,
        BLACK = 1
    };

    enum class MoveStatus {
        Default,
        Castle,
        PawnPromotion,
        KillMove,
        NotValid
    };

    enum class Types {
        Rock = 4,
        Knight = 3,
        Bishop = 2,
        Queen = 1,
        King = 0,
        Pawn = 5,
        Any = 6
    };

    class Board;
    class Piece {
    public:
        Piece(const ChessSide &side = ChessSide::WHITE, const Types &type = Types::Pawn);

        [[nodiscard]] const Types &getType() const;
        [[nodiscard]] const ChessSide &getSide() const;
        [[nodiscard]] const bool &isKilled() const;

        void setDeath(const bool &death = true);
        virtual MoveStatus canMove(const Position &currPos, const Position &nextPos, Board *board);

        virtual void name() = 0;

    protected:
        virtual MoveStatus checkCollision(const Position &currPos, const Position &nextPos, const Board *board);

    private:
        Position getDirection(const int &deltaX, const int &deltaY);
        virtual MoveStatus moveStrategy(const Position &currPos, const Position &nextPos, const Board *board) = 0;

    private:
        const Types type;
        const ChessSide side;
        bool death = false;
    };
}

#endif //CHESS_PIECE_H
