#include <SFML/Graphics.hpp>
#include <iostream>

#include "Render.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Chess");
    auto *r = new Render(window);

    r->initBoard("./board.png");
    r->initFigures("./figures.png");
    r->run();

    return 0;
}