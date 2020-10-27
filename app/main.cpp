#include <SFML/Graphics.hpp>
#include <iostream>

//#include "Board.h"
#include "Move.h"
#include "Game.h"
#include "Piece.h"

int map[8][8] = {
        -5, -4, -3, -2, -1, -3, -4, -5,
        -6, -6, -6, -6, -6, -6, -6, -6,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 4, 3, 2, 1, 3, 4, 5,
};


int size = 133;
using  namespace Chess;
int spotSize = 100;

Position translateCords(const sf::Vector2f &pos) {
    return {int(pos.y / spotSize), int(pos.x / spotSize)};
}

int main() {
    // create the window
//    Game *game = new Game({std::make_unique<Player>(Player(ChessSide::WHITE, "Player1")),
//                           std::make_unique<Player>(Player(ChessSide::BLACK, "Player2"))});
    Game *game = new Game({Player(ChessSide::WHITE), Player(ChessSide::BLACK)});
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Chess");
    sf::Sprite sprites[32];

    sf::Texture board, figures;
    board.loadFromFile("./board.png");
    figures.loadFromFile("./figures.png");

    for (int i = 0; i < 32; i++) {
        sprites[i].setTexture(figures);
    }
    int k = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            int n = map[i][j];
            if (!n) {
                continue;
            }
            int x = abs(n) - 1;
            int y = n > 0 ? 1: 0;
            sprites[k].setTextureRect(sf::IntRect(size * x, size * y, size, size));
            sprites[k].scale(sf::Vector2f(0.75, 0.75));
            sprites[k].setPosition(100 * j, 100 * i);
            k++;
        }
    }

    sf::Sprite s_board;
    s_board.setTexture(board);

    bool isTook = false;
    int n = 0;
    Position pos = {0, 0};
    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                for (int i = 0; i < 32; ++i) {
                    if (!isTook) {
                        if (sprites[i].getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            std::cout << "1\n";
                            pos = translateCords(sprites[i].getPosition());
                            std::cout << "2\n";
                            if (game->isCurrTurn(pos)) {
                                isTook = !isTook;
                                n = i;
                            }
                            std::cout << "3\n";
                            break;
                        }
                    } else {
                        auto currPos = sprites[n].getPosition() + sf::Vector2f(50, 50);
                        sf::Vector2f newPos = sf::Vector2f(100 * int(currPos.x / 100), 100 * int(currPos.y / 100));
                        if (game->getMove()->getMoveStatus(pos, translateCords(newPos)) != MoveStatus::NotValid) {
                            sprites[n].setPosition(newPos.x, newPos.y);
                            isTook = !isTook;
                        }
                        std::cout << "not Valid\n";
                        break;
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved && isTook) {
                sprites[n].setPosition(event.mouseMove.x - 50, event.mouseMove.y - 50);

            }
        }


        window.clear();


        window.draw(s_board);
        for (int i = 0; i < 32; ++i) window.draw(sprites[i]);

        // end the current frame
        window.display();
    }

    return 0;
}