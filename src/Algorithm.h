#pragma once
#include <string>
#include <vector>
#include <thread>
#include <iostream>
#include "Graph/Graph.h"
#include "SharedState.h"

// initial reserved size for the m_operations vector
#define OPERATIONS_RESERVED_SIZE 1024

#define NANOSECS_FLOAT 1000000000.f

#define FPS 60.f

#define LENGTH_FACTOR(len) 0.5f + (len / 1000.f)

#define CALCULATE_SLEEP_TIME(real_speed, total_items) \
    static_cast<std::int64_t>( \
        ((NANOSECS_FLOAT / FPS) / (real_speed)) / (LENGTH_FACTOR(total_items)) \
    )

class Algorithm {
    // Vector of operations to perform on the graph
    std::vector<std::string> m_operations;
    std::thread m_sorting_thread;

public:
    Algorithm();

    /**
     * @brief Loads all the operations from stdin to the m_operations vector.
     *
     * No checks are performed on the operations.
    */
    void loadOperationsFromStdin();

    /**
     * @brief Spanws the sorting thread and detaches it.
    */
    void spawnThread(Graph* graph, SharedState& shared_state);

private:
    /**
     * @brief The the sorting thread. It will perform all the operations in the
     * m_operations vector.
     *
     * This thread is spawned by the spawnThread() method when the array data
     * has been loaded into the graph.
    */
    void sortingThread(Graph* graph, SharedState& shared_state);
};
