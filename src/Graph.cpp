#include <vector>
#include <iostream>
#include "Graph.h"

void Graph::execute(std::string operation) {
    std::cout << "executing " << operation << "\n";
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
