#include <SFML/Graphics.hpp>
#include <iostream>

#include "Render.h"

int main() {
    sf::VideoMode desktop =  sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(1200, 800, desktop.bitsPerPixel), "Chess", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    auto *r = new Render(window);

    r->initBoard("./board.png");
    r->initFigures("./figures.png");
    r->run();
    delete r;
    return 0;
}