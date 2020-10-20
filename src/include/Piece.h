//
// Created by Artem Shemidko on 19.10.2020.
//

#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#define BLACK 0
#define WHITE 1

namespace Chess {
    class Piece {
    public:
        Piece(const bool &side);
        ~Piece() = default;

        [[nodiscard]] int getSide() const;
        [[nodiscard]] bool isKilled() const;

        void setDeath(const bool &death = true);

    private:
        const bool side;
        bool death = false;
    };
}

#endif //CHESS_PIECE_H
