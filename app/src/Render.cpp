//
// Created by Artem Shemidko on 27.10.2020.
//

#include "Render.h"

#include <iostream>
#include <vector>


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

void Render::initFigures(const std::string &fPath) {
    if (!tFigures.loadFromFile(fPath)) {
        throw "Invalid file path to load figures texture\n";
    }

    auto boardSize = tFigures.getSize();
    figureSize = sf::Vector2f(boardSize.x / 6, boardSize.y / 2);

    auto board = game->getBoard();

    int k = 0;
    for (const auto &it : board->getBoard()) {
       for (const auto &spot : it) {
           if (auto piece = spot->getPiece()) {
               figures[k] = std::make_unique<sf::Sprite>(tFigures);
               figures[k]->setTextureRect(sf::IntRect(figureSize.x * static_cast<int>(piece->getType()),
                                                      figureSize.y * static_cast<int>(piece->getSide()),
                                                      figureSize.x,
                                                      figureSize.y));
               figures[k]->scale(sf::Vector2f(spotSize.x / figureSize.x, spotSize.y / figureSize.y));
               figures[k]->setPosition(spotSize.x * spot->getPos().second, spotSize.y * spot->getPos().first);
               ++k;
           }
       }
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
    bool isMove = false;
    sf::Sprite *n;

    sf::RectangleShape rect;
    rect.setSize(spotSize);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(255, 0, 0));
    rect.setOutlineThickness(-5);

    while (window.isOpen()) {
        window.clear();
        window.draw(*board);
        for (const auto &figure : figures) {
            if (figure.get()) {
                window.draw(*figure);
            }
        }
        if (isMove) {
            window.draw(rect);
            drawPossibleMoves(toPosition(n->getPosition()));
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
                    if (!isMove) {
                        for (const auto & figure : figures) {
                            if (figure->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                                if (game->isCurrTurn(toPosition(figure->getPosition()))) {
                                    std::cout << "ok\n";
                                    n = figure.get();
                                    isMove = true;
                                    rect.setPosition(figure->getPosition());
                                } else
                                    std::cout << "Opponent`s move\n";
                                break;
                            }
                        }
                    } else {
                        auto mouseCords = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
                        auto newPos = 100.f * sf::Vector2f(mouseCords.x / 100, mouseCords.y / 100);
                        isMove = false;
                        n->setPosition(newPos.x, newPos.y);
//                        game->isCheck();
                    }
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
    return sf::Vector2f(cords.second * spotSize.y, cords.first * spotSize.x);

}

void Render::drawPossibleMoves(const Chess::Position &pos) {
    const auto board = game->getBoard();
    const auto &availiblePos = board->getSpot(pos)->getPiece()->getAvailibleMoves(pos, board);
    sf::RectangleShape possibleMove;

    possibleMove.setSize(spotSize);
    possibleMove.setFillColor(sf::Color::Transparent);
    possibleMove.setOutlineColor(sf::Color(255, 255, 0));
    possibleMove.setOutlineThickness(-5);

    for (const auto &it : availiblePos) {
        possibleMove.setPosition(toVector(it));
        window.draw(possibleMove);
    }
}
