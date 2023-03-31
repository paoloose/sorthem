#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Graph.h"

#define MAX_OPERATIONS_PER_FRAME 100

class SorthemApp {
    sf::RenderWindow m_window;
    // Graph object. Must lock the mutex while accesing to it
    Graph m_graph;
    std::mutex m_queue_mutex;
    std::queue<std::string> m_operations_queue;
    sf::Event m_event;
    bool m_sorting = false;
    bool m_loading_data = false;
    std::string m_process_cmd = "node ./examples/bubble_sort.js";

public:
    /**
     * @brief Construct a new Sorthem App object.
     * The arguments will be passed to the sf::RenderWindow constructor.
    */
    SorthemApp(sf::VideoMode win_mode, sf::Uint32 style);
    ~SorthemApp() = default;
    void mainLoop();

private:
    void readProcessOperationsThread(FILE* pipe);
    void handleEvent();
};
