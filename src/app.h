#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>

class SorthemApp {
    sf::RenderWindow m_window;
    std::vector<sf::RectangleShape> m_rectangles;
    bool m_sorting = false;
    std::vector<std::string> operations;
    std::mutex m_mutex;

public:
    SorthemApp(sf::VideoMode win_mode, sf::Uint32 style);
    void mainLoop();

private:
    void constructRectangles(
        std::vector<sf::RectangleShape> &rectangles,
        std::size_t count,
        sf::Vector2f win_size
    );
    void resizeRectangles(
        std::vector<sf::RectangleShape> &rectangles,
        sf::Vector2f old_win_size,
        sf::Vector2f new_win_size
    );
    void readOnThread(FILE* pipe);
};
