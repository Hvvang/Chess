//
// Created by Artem Shemidko on 27.10.2020.
//

#include "Render.h"

#include <iostream>
#include <vector>


Render::Render(sf::RenderWindow &window)
        : window(window)
        , game(new Chess::Game({Chess::Player(Chess::ChessSide::WHITE, "White player"), Chess::Player(Chess::ChessSide::BLACK, "Black player")})){
    font.loadFromFile("sansation.ttf");
}

void Render::initBoard(const std::string &fPath) {
    if (!tBoard.loadFromFile(fPath)) {
        throw std::runtime_error("Invalid file path to load field texture\n");
    }
    auto boardSize = tBoard.getSize();
    spotSize = sf::Vector2f(boardSize.x / 8.f, boardSize.y / 8.f);
    board = std::make_unique<sf::Sprite>(tBoard);
}

void Render::initFigures(const std::string &fPath) {
    if (!tFigures.loadFromFile(fPath)) {
        throw std::runtime_error("Invalid file path to load figures texture\n");
    }
    auto boardSize = tFigures.getSize();
    figureSize = sf::Vector2f(boardSize.x / 6.f, boardSize.y / 2.f);
    updatePiecesPosition();
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
    sf::RectangleShape rect;
    rect.setSize(spotSize);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(255, 0, 0));
    rect.setOutlineThickness(-5);

    window.clear();
    window.draw(*board);
    drawInfoPanel();
    updatePiecesPosition();
    for (auto &figure : figures) {
        window.draw(*figure);
    }
//    renderCheckStatus(Chess::GameStatus::Default);
    window.display();

    //    TODO: this func requires to be refactored (a lot of code repeating and etc);
    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                auto pos = toPosition(sf::Vector2f(mousePos.x, mousePos.y));
                auto gameStatus = game->makeMove(pos);

                window.clear();
                window.draw(*board);
                drawInfoPanel();
                switch (gameStatus) {
                case Chess::GameStatus::Default:
                    updatePiecesPosition();
                    break;

                case Chess::GameStatus::KingCheck:
                    drawMessageInLog("Move is forbidden because\n of king check.\nTry again!");
                    break;

                case Chess::GameStatus::InvalidMove:
                    drawMessageInLog("Move is forbidden because\nof not valid move strategy.\nTry again!");
                    break;

                case Chess::GameStatus::Castle:
                    drawMessageInLog("Player make king castle.");
                    updatePiecesPosition();
                    break;

                case Chess::GameStatus::InvalidCastle:
                    drawMessageInLog("Castle is forbidden if:\n  "
                                     "king has made move;\n  "
                                     "rock has made move;\n  "
                                     "king gets checking during\nthis move.\n"
                                     "Try again!");
                    break;

                case Chess::GameStatus::PieceAnotherPlayer:
                    drawMessageInLog("Can't select opponent\npiece.\n"
                                     "Try again!");
                    break;


                case Chess::GameStatus::PieceSelected:
                    rect.setPosition(toVector(pos));
                    window.draw(rect);
                    drawPossibleMoves(pos);
                    drawMessageInLog("Piece is selected");
                    break;

                case Chess::GameStatus::PieceUnSelected:
                    drawMessageInLog("Piece is unselected");
                    break;

                case Chess::GameStatus::PieceNotSelected:
                    drawMessageInLog("Any piece is not selected");
                    break;

                }
                renderCheckStatus(game->getCheckStatus());
                for (const auto &figure : figures) {
                    window.draw(*figure);
                }
                window.display();
            }
        }
    }
}

const std::unique_ptr<sf::Sprite> &Render::getBoard() const {
    return board;
}

void Render::gameOver() {
    sf::Text text("Game over", font);
    text.setCharacterSize(60);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(spotSize.x * 2.5, spotSize.y * 4);
    window.draw(text);
}

// translate sf::Vector2f cords to Position cords using in Game
Chess::Position Render::toPosition(const sf::Vector2f &cords) const {
    return Chess::Position(static_cast<int>(cords.y / spotSize.y), static_cast<int>(cords.x / spotSize.x));
}

// translate Position cords to sf::Vector2f cords using in Rendering
sf::Vector2f Render::toVector(const Chess::Position &cords) const {
    return sf::Vector2f(cords.second * spotSize.y, cords.first * spotSize.x);
}

void Render::drawPossibleMoves(const Chess::Position &pos) {
    const auto board = game->getBoard();
    const auto &availablePos = board->getSpot(pos)->getPiece()->getAvailableMoves(pos, board);
    sf::RectangleShape possibleMove;

    possibleMove.setSize(spotSize);
    possibleMove.setFillColor(sf::Color::Transparent);
    possibleMove.setOutlineColor(sf::Color(255, 255, 0));
    possibleMove.setOutlineThickness(-5);

    for (const auto &it : availablePos) {
        possibleMove.setPosition(toVector(it));
        window.draw(possibleMove);
    }
}

void Render::updatePiecesPosition() {
    auto board = game->getBoard();

    auto pieceSpots = board->getSpotsByChessSide(Chess::ChessSide::WHITE);
    const auto &blackPieceSpots = board->getSpotsByChessSide(Chess::ChessSide::BLACK);

    pieceSpots.insert(pieceSpots.end(), blackPieceSpots.begin(), blackPieceSpots.end());
    figures.clear();
    for (const auto &spot : pieceSpots) {
        sf::Sprite piece(tFigures);

        piece.setTextureRect(sf::IntRect(figureSize.x * static_cast<int>(spot->getPiece()->getType()),
                                          figureSize.y * static_cast<int>(spot->getPiece()->getSide()),
                                          figureSize.x,
                                          figureSize.y));
        piece.scale(sf::Vector2f(spotSize.x / figureSize.x, spotSize.y / figureSize.y));
        piece.setPosition(spotSize.x * spot->getPos().second, spotSize.y * spot->getPos().first);
        figures.push_back(std::make_unique<sf::Sprite>(piece));
    }
}

void Render::renderCheckStatus(const Chess::GameStatus &checkStatus) {
    if (checkStatus != Chess::GameStatus::Default) {
        std::string str = game->getCurrPlayer().getName();
        if (checkStatus == Chess::GameStatus::KingCheck) {
            str += " get king check";
        } else if (checkStatus == Chess::GameStatus::KingStaleMate) {
            str += " lose because\nof stalemate";
        } else if (checkStatus == Chess::GameStatus::KingCheckMate) {
            str += " lose because\nof checkmate";
        }
        sf::RectangleShape rect;
        rect.setSize(spotSize);
        rect.setFillColor(sf::Color::Red);
        auto pos = game->getBoard()->getSpot(Chess::Types::King, game->getCurrPlayer().getSide())->getPos();
        rect.setPosition(toVector(pos));
        window.draw(rect);
        sf::Text text(str, font);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition(spotSize.x * 8 + spotSize.x / 3, spotSize.y * 4);
        window.draw(text);
    }
}
void Render::drawInfoPanel() {
    auto pos = sf::Vector2f(spotSize.x * 8.f, 0);

    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(spotSize.x * 4, spotSize.y * 8));
    rect.setFillColor(sf::Color(255,230,190));
    rect.setPosition(pos);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    rect.setOutlineThickness(-5);
    window.draw(rect);
    rect.setSize(sf::Vector2f(spotSize.x * 4, spotSize.y));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color(0, 0, 0));
    rect.setOutlineThickness(-3);
    window.draw(rect);
    sf::Text text(game->getCurrPlayer().getName() + " turn", font);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(pos.x + spotSize.x / 4, spotSize.y / 3);
    window.draw(text);
    text.setString("Info log:");
    text.setPosition(pos.x + spotSize.x / 5, spotSize.y * 1.25 );
    window.draw(text);
    text.setString("Check log:");
    text.setPosition(pos.x + spotSize.x / 5, spotSize.y * 3.5 );
    window.draw(text);
}
void Render::drawMessageInLog(const std::string &message) {
    sf::Text text(message, font);
    text.setCharacterSize(28);
    text.setFillColor(sf::Color(0, 0, 0));
    text.setPosition(spotSize.x * 8 + spotSize.x / 3, spotSize.y *  1.75);
    window.draw(text);
}
