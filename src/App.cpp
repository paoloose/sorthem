#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include "App.h"

SorthemApp::SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
    m_window(),
    m_graph(&m_window.getView()),
    m_algorithm()
{
    std::cout << "\nLoading data...\n";
    m_graph.loadArrayDataFromStdin();

    std::cout << "Loading operations...\n";
    m_algorithm.loadOperationsFromStdin();

    std::cout << "Done\n";
    m_window.create(win_mode, "sorthem", style);
    m_graph.loadRectsValues();

    m_algorithm.spawnThread(&m_graph, m_shared_state);
}

void SorthemApp::mainLoop() {
    float dt;
    while (m_window.isOpen()) {
        dt = m_clock.restart().asSeconds();
        (void)dt; // TODO: use dt to calculate the real speed

        while (m_window.pollEvent(m_event)) {
            /* interact with input (UI) */
            handleEvent();
        }
        /* update UI */
        // TODO: no UI yet

        /* draw */
        m_window.clear();
        m_window.draw(m_graph);
        m_window.display();
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
            if (m_shared_state.isFinished()) {
                m_graph.resetBarStates();
                m_shared_state.setOperationIndex(0);
                m_shared_state.setIsFinished(false);
            }
            else {
                bool is_paused = m_shared_state.isPaused();
                m_shared_state.setIsPaused(!is_paused);
            }
        }
        if (m_event.key.code == sf::Keyboard::R) {
            m_graph.resetBarStates();
            m_shared_state.setOperationIndex(0);
            m_shared_state.setIsFinished(false);
            m_shared_state.setIsPaused(true);
        }
        if (m_event.key.code == sf::Keyboard::Up) {
            float new_user_speed = m_shared_state.getUserSpeed() + 0.05f;
            m_shared_state.setUserSpeed(new_user_speed);
        }
        if (m_event.key.code == sf::Keyboard::Down) {
            float new_user_speed = m_shared_state.getUserSpeed() - 0.05f;
            if (new_user_speed < 0.01f) {
                new_user_speed = 0.01f;
            }
            m_shared_state.setUserSpeed(new_user_speed);
        }
        /* Dump array to the program */
        if (m_event.key.code == sf::Keyboard::D && m_shared_state.isPaused()) {
            // non implemented yet
        }
    }
}
