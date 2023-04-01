#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>
#include "Graph.h"

#define MAX_OPERATIONS_PER_FRAME 10

class SorthemApp {
    sf::RenderWindow m_window;
    // Graph object. Must lock the mutex while accesing to it
    Graph m_graph;
    sf::Event m_event;

    // Queue of operations to perform on the graph
    std::queue<std::string> m_operations_queue;
    std::mutex m_queue_mutex;

    /* Application flags */

    // Whether the program is sorting and animating the bars
    bool m_sorting = false;

    // Whether the program is loading the array data from the child process
    bool m_loading_array_data = false;

    // Whether the program is loading the operations from the child process
    // (this is not always synchronized with m_sorting, since the operations
    //  are loaded in a different thread and can finish after the sorting)
    bool m_loading_operations = false;

    // Command to execute the sorting program (currently hardcoded)
    std::string m_process_cmd = "node ./examples/bubble_sort.js";

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
     * @brief The starting point of the read-operations thread.
     *
     * It receives a pipe to the sorting process and starts reading and
     * executing the sort operations in real time.
     *
     * While the thread is running, the m_loading_operations flag is set to true.
    */
    void readProcessOperationsThread(FILE* pipe);

    /**
     * @brief Handles the events polled by the main loop.
    */
    void handleEvent();
};
