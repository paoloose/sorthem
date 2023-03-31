#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include "App.h"

SorthemApp::SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
    m_window(win_mode, "sorthem", style),
    m_graph(1000)
{
    m_graph.constructRectangles(m_window.getView().getSize());
}

void SorthemApp::readOnThread(FILE* pipe) {
    /* open program */
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        // Send output to main thread
        std::string output = buffer;
        if (m_mutex.try_lock()) {
            operations.push_back(output);
            std::cout << "pushing: " << output << "\n";
            m_mutex.unlock();
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
            FILE* pipe = popen("python3 examples/merge_sort.py", "r");

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
        if (m_mutex.try_lock()) {
            for (auto& operation : operations) {
                std::cout << "popping: " << operation << "\n";
                m_graph.execute(operation);
            }
            operations.clear();
            m_mutex.unlock();
        }
        /* update UI */
        m_window.clear();

        /* draw */
        m_window.draw(m_graph);
        m_window.display();
    }
}
