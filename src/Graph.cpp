#include <vector>
#include <iostream>
#include <sstream>
#include "Graph.h"

void Graph::execute(std::string operation) {
    if (operation.empty()) return;
    std::istringstream iss(operation);
    std::string command;
    iss >> command;

    if (command == "swap") {
        long int a, b;
        iss >> a >> b;
        if (iss.fail()) {
            throw std::runtime_error("error executing swap command: " + operation);
        }
        // check for index out of range
        if (a < 0 || b < 0) {
            throw std::runtime_error("swap: out of range");
        }

        this->swap(static_cast<size_t>(a), static_cast<size_t>(b));
    }
    else {
        std::cout << "unknown operation: " << operation << "\n";
    }
}

void Graph::swap(size_t a, size_t b) {
    size_t bars_num = m_bars.size();
    if (a >= bars_num || b >= bars_num) {
        throw std::runtime_error("swap: out of range");
    }

    Bar &bar_a = m_bars[a];
    Bar &bar_b = m_bars[b];

    sf::Vector2f bar_a_pos = bar_a.getPosition();
    sf::Vector2f bar_b_pos = bar_b.getPosition();
    bar_a.setPosition({ bar_b_pos.x, bar_a_pos.y });
    bar_b.setPosition({ bar_a_pos.x, bar_b_pos.y });
    // colorize
    bar_a.setState(Bar::state::Swapping);
    bar_b.setState(Bar::state::Swapping);
    std::swap(bar_a, bar_b);
}

Graph::Graph(int bars_number) : m_bars(bars_number) { }

void Graph::constructRectangles(sf::Vector2f win_size) {
    size_t count = m_bars.size();
    float rects_width = win_size.x / count;
    for (std::size_t i = 0; i < count; i++) {
        float random_height = (std::rand() % static_cast<int>(win_size.y)) + 1;
        m_bars[i].setSize({ rects_width, random_height });
        m_bars[i].setPosition({ i * rects_width, win_size.y - random_height });
        // rectangles[i].setFillColor(sf::Color::Red);
    }
}

void Graph::resize(sf::Vector2f old_win_size, sf::Vector2f new_win_size) {
    size_t count = m_bars.size();
    if (count == 0) return;
    float new_width = new_win_size.x / count;
    for (std::size_t i = 0; i < count; i++) {
        Bar& rect = m_bars[i];
        float new_heigth = new_win_size.y * rect.getSize().y / old_win_size.y;
        rect.setSize({ new_width, new_heigth });
        rect.setPosition({ i * new_width, new_win_size.y - new_heigth });
    }
}

void Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto& bar : m_bars) {
        target.draw(bar, states);
    }
}

void Graph::refreshBarStates() {
    for (auto& bar : m_bars) {
        bar.refreshState();
    }
}
