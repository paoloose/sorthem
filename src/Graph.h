#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <string>
#include "Bar.h"

typedef float bar_height_t;
#define STR_TO_BAR_HEIGHT_T(str) std::stof((str))

class Graph : public sf::Drawable {
    std::vector<Bar> m_bars;
    // Points to the view of the window
    const sf::View* m_win_view;
    bar_height_t m_max_height;
  public:
    /**
     * @brief Execute an operation on the sorting graph.
    */
    void execute(std::string operation);
    Graph(int bars_number, const sf::View* win_view);
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

    void swap(size_t index_a, size_t index_b);
    void compare(size_t index_a, size_t index_b);
    void set(size_t index, bar_height_t absolute_value);
    void get(size_t index);
    void refreshBarStates();
    void loadDataFromProcess(FILE* pipe, bool* loading);
    void loadDataFromProcessThread(FILE* pipe, bool* loading);
};
