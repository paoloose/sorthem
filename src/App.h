#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Graph.h"

class SorthemApp {
    sf::RenderWindow m_window;
    bool m_sorting = false;
    Graph m_graph;
    std::vector<std::string> operations;
    std::mutex m_mutex;
    sf::Event m_event;

public:
    /**
     * @brief Construct a new Sorthem App object.
     * The arguments will be passed to the sf::RenderWindow constructor.
    */
    SorthemApp(sf::VideoMode win_mode, sf::Uint32 style);
    ~SorthemApp() = default;
    void mainLoop();

private:
    void readOnThread(FILE* pipe);
    void handleEvent();
};
