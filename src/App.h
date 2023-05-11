#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Graph/Graph.h"
#include "Algorithm.h"
#include "SharedState.h"

class SorthemApp {
    sf::RenderWindow m_window;
    Graph m_graph;
    Algorithm m_algorithm;
    sf::Event m_event;
    sf::Clock m_clock;
    // The application state shared with the sorting thread
    SharedState m_shared_state;

public:
    /**
     * @brief Construct a new Sorthem App object.
     * The arguments will be passed to the sf::RenderWindow constructor.
    */
    SorthemApp(sf::VideoMode win_mode, sf::Uint32 style);
    ~SorthemApp() = default;

    /**
     * @brief Main loop of the Sorthem application.
    */
    void mainLoop();

private:
    /**
     * @brief Handles the events polled by the main loop.
    */
    void handleEvent();
};
