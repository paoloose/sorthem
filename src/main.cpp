#include <SFML/Graphics.hpp>
#include "app.h"

#define WIN_HEIGHT 600
#define WIN_WIDTH 800

int main() {
    SorthemApp sorthem(
        sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
        sf::Style::Default
    );
    sorthem.mainLoop();

    return 0;
}
