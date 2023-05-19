#include <string>
#include <SFML/Graphics.hpp>
#include "App.h"
#include "cli/helpers.h"
#include "config.h"

int main(void) {
    exit_if_bad_usage();

    SorthemApp sorthem(
        sf::VideoMode(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT),
        sf::Style::Default
    );
    sorthem.mainLoop();

    return 0;
}
