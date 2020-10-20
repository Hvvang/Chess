//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <utility>

namespace Chess {
    #define BLACK 0
    #define WHITE 1

    class Piece {
    public:
        Piece(const bool &side = WHITE, std::pair<int, int> pos = {0, 0});
        ~Piece() = default;

        [[nodiscard]] int getSide() const;
        [[nodiscard]] bool isKilled() const;
        [[nodiscard]] std::pair<int, int> getPosition() const;

        void setDeath(const bool &death = true);
        void setPosition(std::pair<int, int> pos);
        virtual bool moveStrategy(std::pair<int, int> nextPos) = 0;

    private:
        int x;
        int y;
        const bool side;
        bool death = false;
    };
}

#endif //CHESS_PIECE_H
