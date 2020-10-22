//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Piece.h"
#include <array>
#include <memory>

namespace Chess {
#define BOARD_COLS 8
#define BOARD_ROWS 8
    template<class T>
    using Field = std::array<std::array<T, BOARD_COLS>, BOARD_ROWS>;

    using Position = std::pair<int, int>;

    class Piece;
    class Board final {
    public:
        Board();
        ~Board() = default;

        void initBoard();
        void reset();

        Piece *getSpot(const Position &pos) const;

        [[nodiscard]] Field<std::unique_ptr<Piece>> &getBoard();

    private:
        Field<std::unique_ptr<Piece>> board;

        const int size = 400;
    };

}
#endif //CHESS_BOARD_H
