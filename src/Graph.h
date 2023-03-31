#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Bar.h"

class Graph : public sf::Drawable {
    std::vector<Bar> m_bars;
  public:
    /**
     * @brief Execute an operation on the sorting graph.
    */
    void execute(std::string operation);
    Graph(int bars_number);
    /**
     * @brief Initialize the bars and set their positions.
     *
     * This function should be called only once, when the window is created.
    */
    void constructRectangles(sf::Vector2f win_size);
    /**
     * @brief Resize the bars and set their positions.
     *
     * This function should be called every time the window is resized.
    */
    void resize(sf::Vector2f old_win_size, sf::Vector2f new_win_size);
    /**
     * @brief Draws the entire graph.
    */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
