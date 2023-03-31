#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include "App.h"

#define N_ELEMENTS 48

SorthemApp::SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
    m_window(win_mode, "sorthem", style),
    m_graph(N_ELEMENTS)
{
    m_graph.constructRectangles(m_window.getView().getSize());
}

void SorthemApp::readOnThread(FILE* pipe) {
    /* open program */
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Send output to main thread
        std::string operation = buffer;
        if (m_graph_mutex.try_lock()) {
            /* clear previous states */
            m_graph.refreshBarStates();
            /* execute */
            std::cout << "executing: " << operation << "\n";
            m_graph.execute(operation);
            m_graph_mutex.unlock();
        }
    }
    std::cout << "closing pipe\n";
    pclose(pipe);
    m_sorting = false;
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
        if (m_event.key.code == sf::Keyboard::Space && !m_sorting) {
            /* open the program once */
            m_sorting = true;
            // Start child process and redirect its stdout to a pipe
            FILE* pipe = popen("node ./examples/bubble_sort.js", "r");

            // Start thread to read output from pipe
            std::thread read_thread(&SorthemApp::readOnThread, this, pipe);
            read_thread.detach();
        }
    }
}

void SorthemApp::mainLoop() {
    while (m_window.isOpen()) {
        while (m_window.pollEvent(m_event)) {
            handleEvent();
        }

        /* interact with input (UI) */
        /* read operations and execute operations */
        // moved to the read_thread
        // if (m_mutex.try_lock()) {
        //     for (auto& operation : operations) {
        //         std::cout << "popping: " << operation << "\n";
        //         m_graph.execute(operation);
        //     }
        //     operations.clear();
        //     m_mutex.unlock();
        // }
        /* update UI */
        m_window.clear();

        /* draw */
        m_window.draw(m_graph);
        m_window.display();
    }
}
