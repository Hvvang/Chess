#include <SFML/Graphics.hpp>
#include <iostream>

#include "Render.h"

#include "Move.h"
#include "Game.h"
#include "Piece.h"

using namespace Chess;

int main() {
    // create the window
//    Game *game = new Game({std::make_unique<Player>(Player(ChessSide::WHITE, "Player1")),
//                           std::make_unique<Player>(Player(ChessSide::BLACK, "Player2"))});
//    Game *game = new Game({Player(ChessSide::WHITE), Player(ChessSide::BLACK)});
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "Chess");

    Render *r = new Render(window);

    r->initBoard("./board.png");
    r->initFigures("./figures.png");

    r->draw();

//                    } else {
//                        auto currPos = sprites[n].getPosition() + sf::Vector2f(50, 50);
//                        sf::Vector2f newPos = sf::Vector2f(100 * int(currPos.x / 100), 100 * int(currPos.y / 100));
//                        if (game->getMove()->getMoveStatus(pos, translateCords(newPos)) != MoveStatus::NotValid) {
//                            sprites[n].setPosition(newPos.x, newPos.y);
//                            game->getMove()->changePosition(pos, translateCords(newPos));
//                            isTook = !isTook;
//                        }
//                        else {
//                            std::cout << "not Valid\n";
//                        }
//                        break;
//                    }
//                }
//            }
//            if (event.type == sf::Event::MouseMoved && isTook) {
//                sprites[n].setPosition(event.mouseMove.x - 50, event.mouseMove.y - 50);
//
//            }
//        }
    return 0;
}