#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <chrono>
#include "App.h"

SorthemApp::SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
    m_window(win_mode, "sorthem", style),
    m_graph(&m_window.getView()),
    m_operations()
{
    m_operations.reserve(OPERATIONS_RESERVED_SIZE);
    std::cout << "\nLoading data...\n\n";
    m_graph.loadArrayDataFromStdin();
    m_graph.loadRectsValues();
    m_array_data_loaded = true;

    std::cout << "\nLoading operations...\n\n";
    this->loadOperationsFromStdin();

    std::cout << "Done\n";
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
        if (m_sorting) {
            // operations per frame
            int max_operations = MAX_OPERATIONS_PER_FRAME;
            while (max_operations--) {
                if (m_operation_index == m_operations.size()) {
                    m_sorting = false;
                    m_finished = true;
                    m_graph.finishAnimation();
                    break;
                }
                m_graph.refreshBarStates();
                m_graph.execute(m_operations[m_operation_index]);
                std::cout << "executing: " << m_operation_index << "\n";
                std::cout << "executing: " << m_operations.size() << "\n";
                m_operation_index++;
            }
        }

        m_window.clear();
        /* draw */
        m_window.draw(m_graph);
        m_window.display();
    }
}

// TODO: there is a delay on fgets when the last operation is executed
void SorthemApp::loadOperationsFromStdin() {
    /* open program */
    std::string operation;
    while (std::getline(std::cin, operation)) {
        std::cout << operation << std::endl;
        m_operations.push_back(operation);
    }
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
        if (m_event.key.code == sf::Keyboard::Space) {
            if (m_finished) {
                m_operation_index = 0;
                m_graph.resetBarStates();
                m_finished = false;
            }
            else {
                m_sorting = !m_sorting;
            }
        }
        if (m_event.key.code == sf::Keyboard::R) {
            m_graph.resetBarStates();
            m_operation_index = 0;
            m_finished = false;
            m_sorting = false;
        }
        /* Dump array to the program */
        if (m_event.key.code == sf::Keyboard::D && !m_sorting) {
            // non implemented yet
        }
    }
}
