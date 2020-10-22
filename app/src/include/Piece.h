//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <utility>
#include "Board.h"

namespace Chess {
#define BLACK 0
#define WHITE 1
using Position = std::pair<int, int>;

Position operator+(const Position &left, const Position &right) {
    return {left.first + right.first, left.second + right.second};
}

class Board;
class Piece {
public:
    Piece(const bool &side = WHITE, Position pos = {0, 0});
    ~Piece() = default;

    [[nodiscard]] int getSide() const;
    [[nodiscard]] bool isKilled() const;
    [[nodiscard]] Position getPosition() const;

    void setDeath(const bool &death = true);
    void setPosition(Position pos);

    bool canMove(Position nextPos, Board *board);

protected:
    virtual bool checkCollision(const Position &currPos, const Position &nextPos, const Board *board);

private:
    Position getDirection(const int &deltaX, const int &deltaY);
    virtual bool moveStrategy(const Position &nextPos, const Board *board) = 0;

private:
    Position pos;
    const bool side;
    bool death = false;
};

}

#endif //CHESS_PIECE_H
