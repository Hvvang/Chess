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
    ~Render();

    void initBoard(const std::string &fPath);
    void initFigures(const std::string &fPath);

    void run();

private:
    void updatePiecesPosition();

    void drawInfoPanel();
    void drawInfoInLog(const std::string &message = "");
    void drawSelectedPieceOutline(sf::Vector2f pos);
    void drawPossibleMoves(const Chess::Position &pos);
    void drawCheckStatus(const Chess::GameStatus &checkStatus);
    void drawGameOver();


    Chess::Position toPosition(const sf::Vector2f &cords) const;
    sf::Vector2f toVector(const Chess::Position &cords) const;

private:
    sf::Font font;
    sf::Texture tBoard;
    sf::Texture tFigures;
    sf::RenderWindow &window;
    sf::Vector2f spotSize;
    sf::Vector2f figureSize;
    Chess::Game *game;
    std::unique_ptr<sf::Sprite> board;
    std::vector<std::unique_ptr<sf::Sprite>> figures;
};


#endif //CHESS_RENDER_H
