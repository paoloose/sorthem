#include <SFML/Graphics.hpp>
#include <iostream>
#include "App.h"

#define WIN_HEIGHT 600
#define WIN_WIDTH 800

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: sorthem <process_cmd>" << std::endl;
        return 1;
    }
    std::string process_cmd = argv[1];

    SorthemApp sorthem(
        process_cmd,
        sf::VideoMode(WIN_WIDTH, WIN_HEIGHT),
        sf::Style::Default
    );
    sorthem.mainLoop();

    return 0;
}
