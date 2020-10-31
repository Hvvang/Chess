#include <SFML/Graphics.hpp>
#include <iostream>

#include "Render.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Chess");

    Render *r = new Render(window);

    r->initBoard("./board.png");
    r->initFigures("./figures.png");

    r->draw();
    return 0;
}