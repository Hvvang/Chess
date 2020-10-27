//
// Created by Artem Shemidko on 27.10.2020.
//

#include "Render.h"

#include <iostream>

Render::Render(sf::RenderWindow &window)
        : window(window)
        , game(new Chess::Game({Chess::Player(Chess::ChessSide::WHITE), Chess::Player(Chess::ChessSide::BLACK)})){
    font.loadFromFile("sansation.ttf");
}

void Render::initBoard(const std::string &fPath) {

    if (!tBoard.loadFromFile(fPath)) {
        throw "Invalid file path to load board texture\n";
    }
    auto boardSize = tBoard.getSize();
    spotSize = sf::Vector2f(boardSize.x / 8, boardSize.y / 8);
    board = std::make_unique<sf::Sprite>(tBoard);
}

const int map[8][8] = {
        -5, -4, -3, -2, -1, -3, -4, -5,
        -6, -6, -6, -6, -6, -6, -6, -6,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 4, 3, 2, 1, 3, 4, 5,
};

void Render::initFigures(const std::string &fPath) {
    if (!tFigures.loadFromFile(fPath)) {
        throw "Invalid file path to load figures texture\n";
    }

    auto boardSize = tFigures.getSize();
    figureSize = sf::Vector2f(boardSize.x / 6, boardSize.y / 2);

    auto board = game->getBoard();

    int k = 0;
    int row = 0;
    for (const auto &it : board->getBoard()) {
       for (const auto &spot : it) {
           if (auto piece = spot->getPiece()) {
               figures[k] = std::make_unique<sf::Sprite>(tFigures);
               figures[k]->setTextureRect(sf::IntRect(figureSize.x * static_cast<int>(piece->getType()),
                                                      figureSize.y * static_cast<int>(piece->getSide()),
                                                      figureSize.x,
                                                      figureSize.y));
               figures[k]->scale(sf::Vector2f(spotSize.x / figureSize.x, spotSize.y / figureSize.y));
               figures[k]->setPosition(spotSize.x * (k % 8), spotSize.y * row);
               ++k;
           }
       }
       ++row;
    }
}

void Render::clearFigures() {
    for (auto &it : figures) {
        it.reset();
    }
}

void Render::removeFigure(std::unique_ptr<sf::Sprite> *figure) {
    figure->reset();
}

void Render::draw() {

    while (window.isOpen()) {
        window.clear();
        window.draw(*board);
        for (int i = 0; i < 32; ++i) {
            if (figures[i].get()) {
                window.draw(*figures[i]);
            }
        }
        window.display();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < 32; ++i) {
                        if (figures[i]->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            if (game->isCurrTurn(toPosition(figures[i]->getPosition()))) {
                                std::cout << "ok\n";
                            } else
                                std::cout << "Opponent`s move\n";
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {

                }
            }
        }
    }
}



sf::RenderWindow &Render::getWindow() const {
    return window;
}

const std::unique_ptr<sf::Sprite> &Render::getBoard() const {
    return board;
}

const std::unique_ptr<sf::Sprite> *Render::getFigures() const {
    return figures;
}

void Render::gameOver() {
    sf::Text text("Game over", font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(spotSize.x * 2.5, spotSize.y * 4);
}

Chess::Position Render::toPosition(sf::Vector2f cords) const {
    return Chess::Position(static_cast<int>(cords.y / spotSize.y), static_cast<int>(cords.x / spotSize.x));
}

sf::Vector2f Render::toVector(Chess::Position cords) const {
    return sf::Vector2f(cords.first * spotSize.x, cords.second * spotSize.y);

}

