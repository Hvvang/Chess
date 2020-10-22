//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <utility>
#include "Board.h"

#include <iostream>


namespace Chess {
    using Position = std::pair<int, int>;

enum class ChessSide {
    WHITE,
    BLACK
};
class Board;
class Piece {
public:
    Piece(const ChessSide &side = ChessSide::WHITE, const Position &pos = {0, 0});
    ~Piece() = default;

    [[nodiscard]] const ChessSide &getSide() const;
    [[nodiscard]] const bool &isKilled() const;
    [[nodiscard]] const Position &getPosition() const;

    void setDeath(const bool &death = true);
    void setPosition(Position pos);

    virtual bool canMove(Position nextPos, Board *board);

protected:
    virtual bool checkCollision(const Position &currPos, const Position &nextPos, const Board *board);

private:
    Position getDirection(const int &deltaX, const int &deltaY);
    virtual bool moveStrategy(const Position &nextPos, const Board *board);

private:
    Position pos;
    const ChessSide side;
    bool death = false;
};

}

#endif //CHESS_PIECE_H
