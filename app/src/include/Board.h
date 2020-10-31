//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "Spot.h"
#include <array>
#include <vector>
#include <memory>

namespace Chess {
#define BOARD_COLS 8
#define BOARD_ROWS 8
    template<class T>
    using Field = std::array<std::array<T, BOARD_COLS>, BOARD_ROWS>;

    using Position = std::pair<int, int>;
    enum class Types;
    enum class ChessSide;
    class Piece;
    class Spot;

    class Board final {
    public:
        Board();
        ~Board() = default;

        void initBoard();
        void reset();

        Spot *getSpot(const Types &type, const ChessSide &side);
        std::vector<Spot *> getSpotsByChessSide(const ChessSide &side);
        [[nodiscard]] Spot *getSpot(const Position &pos) const;
        [[nodiscard]] Field<std::unique_ptr<Spot>> &getField();

    private:
        Field<std::unique_ptr<Spot>> field;
    };

}
#endif //CHESS_BOARD_H
