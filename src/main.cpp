#include <string>
#include <SFML/Graphics.hpp>
#include "cli/helpers.h"
#include "App.h"

#define WIN_HEIGHT 600
#define WIN_WIDTH 800

int main(void) {
    exit_if_bad_usage();

    SorthemApp sorthem(
        sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
        sf::Style::Default
    );
    sorthem.mainLoop();

    return 0;
}
