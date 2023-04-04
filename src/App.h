#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Graph.h"

#define MAX_OPERATIONS_PER_FRAME 1
#define OPERATIONS_RESERVED_SIZE 1024

class SorthemApp {
    sf::RenderWindow m_window;
    // Graph object. Must lock the mutex while accesing to it
    Graph m_graph;
    sf::Event m_event;

    // Vector of operations to perform on the graph
    std::vector<std::string> m_operations;
    size_t m_operation_index = 0;

    /* Application flags */

    // Whether the program is sorting and animating the bars
    bool m_sorting = false;

    // Whether the program has finished the sorting
    bool m_finished = false;

    // Whether the program has laoded the array data from stdin
    bool m_array_data_loaded = false;

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

    /**
     * @brief Loads the stdin input (array data and operations)
    */
    // void loadStdin();

private:
    /**
     * @brief Loads all the operations from stdin to the m_operations vector.
     *
     * No checks are performed on the operations.
    */
    void loadOperationsFromStdin();

    /**
     * @brief Handles the events polled by the main loop.
    */
    void handleEvent();
};
