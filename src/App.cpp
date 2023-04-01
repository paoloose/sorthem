#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include "App.h"

#define N_ELEMENTS 10

SorthemApp::SorthemApp(std::string process_cmd, sf::VideoMode win_mode, sf::Uint32 style) :
    m_process_cmd(process_cmd),
    m_window(win_mode, "sorthem", style),
    m_graph(N_ELEMENTS, &m_window.getView())
{
    m_graph.constructRectangles(m_window.getView().getSize());
}

void SorthemApp::mainLoop() {
    while (m_window.isOpen()) {
        while (m_window.pollEvent(m_event)) {
            /* interact with input (UI) */
            handleEvent();
        }
        /* update UI */
        // TODO: no UI yet

        /* perform operations */
        if (m_sorting && m_queue_mutex.try_lock()) {
            // operations per frame
            int max_operations = MAX_OPERATIONS_PER_FRAME;
            while (!m_operations_queue.empty() && max_operations--) {
                m_graph.refreshBarStates();
                m_graph.execute(m_operations_queue.front());
                m_operations_queue.pop();
            }
            m_queue_mutex.unlock();
            if (m_operations_queue.empty() && !m_loading_operations) {
                m_sorting = false;
                m_graph.finishAnimation();
            }
        }

        m_window.clear();
        /* draw */
        m_window.draw(m_graph);
        m_window.display();
    }
}

// TODO: there is a delay on fgets when the last operation is executed
void SorthemApp::readProcessOperationsThread(FILE* pipe) {
    /* open program */
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Send output to main thread
        std::string operation = buffer;
        m_queue_mutex.lock();
        m_operations_queue.push(operation);
        m_queue_mutex.unlock();
    }
    std::cout << "closing pipe\n";
    m_loading_operations = false;
    pclose(pipe);
}

void SorthemApp::handleEvent() {
    if (m_event.type == sf::Event::Closed) {
        m_window.close();
    }
    else if (m_event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f, m_event.size.width, m_event.size.height);
        sf::Vector2f old_size = m_window.getView().getSize();
        m_window.setView(sf::View(visibleArea));
        m_graph.resize(old_size, m_window.getView().getSize());
    }
    else if (m_event.type == sf::Event::KeyPressed) {
        /* Start sorting (sorting=true, loading_operations=true)*/
        if (m_event.key.code == sf::Keyboard::Space && !m_sorting && !m_loading_array_data) {
            std::cout << "\nSORTING...\n\n";
            /* open the program once */
            // Start child process and redirect its stdout to a pipe
            FILE* pipe = popen(m_process_cmd.c_str(), "r");
            m_sorting = true;
            if (pipe == nullptr) {
                std::cerr << "Failed to open process\n";
                exit(1);
            }

            // Start thread to read output from pipe
            m_loading_operations = true;
            std::thread read_thread(&SorthemApp::readProcessOperationsThread, this, pipe);
            read_thread.detach();
        }
        /* Load array from the program (loading_array_data=true) */
        if (m_event.key.code == sf::Keyboard::L && !m_loading_array_data && !m_sorting) {
            std::cout << "\nLOADING DATA...\n\n";
            m_loading_array_data = true;

            FILE* pipe = popen(m_process_cmd.c_str(), "r");
            if (pipe == nullptr) {
                std::cerr << "Failed to open process\n";
                exit(1);
            }

            m_graph.resetBarStates();
            // Starts a thread and detach it to read output from pipe
            std::thread load_thread(
                &Graph::loadDataFromProcessThread,
                &m_graph,
                pipe,
                &m_loading_array_data
            );
            load_thread.detach();
        }
        /* Dump array to the program */
        if (m_event.key.code == sf::Keyboard::D && !m_sorting) {
            // non implemented yet
        }
    }
}
