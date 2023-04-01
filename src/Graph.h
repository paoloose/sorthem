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
    Graph(int bars_number, const sf::View* win_view);

    /**
     * @brief Execute an operation on the sorting graph.
    */
    void execute(std::string operation);

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

    /**
     * @brief Resets all the bar states to the default state.
    */
    void resetBarStates();

    /**
     * @brief Refreshes all the bar states
    */
    void refreshBarStates();

    /**
     * @brief To indicate that the animation has finished. This will set all the
     * bars to the default state, and will check if the sorting is correct.
    */
    void finishAnimation();

    /**
     * @brief The starting point of the load data thread. The data read from the
     * pipe has the form [ n1 n2 n3 n4 ] (defined by the user.)
     *
     * The data will be read from "[" to "]" and must have the form of:
     * [ 100 234 23 12.2 1.5 ]
     *
     * While executing, `m_loading_array_data` is set to true.
     *
     * On finish, it updates all the graph and sets loading to false.
    */
    void loadDataFromProcessThread(FILE* pipe, bool* loading);

    /* Basic sorting operations (documentend on the README.md) */

    void swap(size_t index_a, size_t index_b);
    void compare(size_t index_a, size_t index_b);
    void set(size_t index, bar_height_t absolute_value);
    void get(size_t index);
    void set_mark(size_t index, std::string mark);
};
