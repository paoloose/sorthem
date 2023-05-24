#include "sorthem/algorithm.h"

namespace sorthem {

Algorithm::Algorithm() : m_operations(), m_sorting_thread() {
    m_operations.reserve(OPERATIONS_RESERVED_SIZE);
}

// TODO: there is a delay on fgets when the last operation is executed
void Algorithm::loadOperationsFromStdin() {
    /* open program */
    std::string operation;
    while (std::getline(std::cin, operation)) {
        m_operations.push_back(operation);
    }
}

void Algorithm::sortingThread(Graph* graph, SharedState& shared_state) {
    while (true) {
        std::size_t operation_index = shared_state.getOperationIndex();
        if (shared_state.isPaused()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }
        if (operation_index >= m_operations.size()) {
            shared_state.setIsPaused(true); // not really needed
            shared_state.setIsFinished(true);
            graph->finishAnimation();
            continue;
        }
        graph->refreshBarStates();
        graph->execute(m_operations[operation_index]);
        shared_state.setOperationIndex(operation_index + 1);

        std::int64_t sleep_time_ns = CALCULATE_SLEEP_TIME(
            shared_state.getRealSpeed(), m_operations.size()
        );
        std::this_thread::sleep_for(std::chrono::nanoseconds(sleep_time_ns));
    }
}

void Algorithm::spawnThread(Graph* graph, SharedState& shared_state) {
    m_sorting_thread = std::thread(
        &Algorithm::sortingThread, this,
        graph, std::ref(shared_state)
    );
    m_sorting_thread.detach();
}

}
