//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Spot.h"
#include <array>
#include <memory>

namespace Chess {

#define BOARD_COLS 8
#define BOARD_ROWS 8

    template<class T>
    using Field = std::array<std::array<T, BOARD_COLS>, BOARD_ROWS>;

    class Board {
    public:
        Board();

        ~Board() = default;

        void initBoard();

        void update();

    private:
        Field<std::unique_ptr<Spot>> board;

        const int size = 400;
    };

}
#endif //CHESS_BOARD_H
