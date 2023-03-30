#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <mutex>
#include "app.h"

#define RECTS_NUMBER 1000

SorthemApp::SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
    m_window(win_mode, "sorthem", style),
    m_rectangles(RECTS_NUMBER)
{
    constructRectangles(m_rectangles, RECTS_NUMBER, m_window.getView().getSize());
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
}

void SorthemApp::mainLoop() {
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
                sf::Vector2f old_size = m_window.getView().getSize();
                m_window.setView(sf::View(visibleArea));
                resizeRectangles(m_rectangles, old_size, m_window.getView().getSize());
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (!m_sorting) {
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
        }

        /* interact with input (UI) */
        /* read operations */
        if (m_mutex.try_lock()) {
            for (auto& operation : operations) {
                std::cout << "popping: " << operation << "\n";
                /* execute operation */
            }
            operations.clear();
            m_mutex.unlock();
        }
        /* execute operations */
        /* update UI */
        /* draw new state */

        m_window.clear();
        /* draw */
        for (auto& rect : m_rectangles) {
            m_window.draw(rect);
        }
        m_window.display();
    }
}

void SorthemApp::constructRectangles(
    std::vector<sf::RectangleShape> &rectangles,
    std::size_t count,
    sf::Vector2f win_size
) {
    float rects_width = win_size.x / count;
    for (std::size_t i = 0; i < count; i++) {
        float random_height = (std::rand() % static_cast<int>(win_size.y)) + 1;
        rectangles[i].setSize({ rects_width, random_height });
        rectangles[i].setPosition({ i * rects_width, win_size.y - random_height });
        // rectangles[i].setFillColor(sf::Color::Red);
    }
}

void SorthemApp::resizeRectangles(
    std::vector<sf::RectangleShape> &rectangles,
    sf::Vector2f old_win_size,
    sf::Vector2f new_win_size
) {
    if (rectangles.size() == 0) return;
    float new_width = new_win_size.x / rectangles.size();
    for (std::size_t i = 0; i < rectangles.size(); i++) {
        sf::RectangleShape& rect = rectangles[i];
        float new_heigth = new_win_size.y * rect.getSize().y / old_win_size.y;
        rect.setSize({ new_width, new_heigth });
        rect.setPosition({ i * new_width, new_win_size.y - new_heigth });
    }
}
