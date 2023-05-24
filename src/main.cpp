#include <string>
#include <SFML/Graphics.hpp>
#include "sorthem/app.h"
#include "sorthem/cli/helpers.h"
#include "sorthem/config.h"

int main(void) {
    sorthem::exit_if_bad_usage();

    sorthem::SorthemApp app(
        sf::VideoMode(INITIAL_WIN_WIDTH, INITIAL_WIN_HEIGHT),
        sf::Style::Default
    );
    app.mainLoop();

    return 0;
}
