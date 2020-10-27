//
// Created by Artem Shemidko on 27.10.2020.
//

#ifndef CHESS_RENDER_H
#define CHESS_RENDER_H

#include <SFML/Graphics.hpp>

#include "Spot.h"
#include "Game.h"

class Render {

public:
    Render(sf::RenderWindow &window);

    void initBoard(const std::string &fPath);
    void initFigures(const std::string &fPath);

    void gameOver();
    void draw();

    void clearFigures();
    void removeFigure(std::unique_ptr<sf::Sprite> *figure);

    Chess::Position toPosition(sf::Vector2f cords) const;
    sf::Vector2f toVector(Chess::Position cords) const;

    [[nodiscard]] sf::RenderWindow &getWindow() const;
    [[nodiscard]] const std::unique_ptr<sf::Sprite> &getBoard() const;
    [[nodiscard]] const std::unique_ptr<sf::Sprite> *getFigures() const;

private:
    sf::Font font;
    sf::Texture tBoard;
    sf::Texture tFigures;
    sf::RenderWindow &window;
    sf::Vector2f spotSize;
    sf::Vector2f figureSize;
    Chess::Game *game;
    std::unique_ptr<sf::Sprite> board;
    std::unique_ptr<sf::Sprite> figures[32];
};


#endif //CHESS_RENDER_H
