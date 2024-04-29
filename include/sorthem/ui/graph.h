#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <string>
#include <sorthem/context.h>
#include <sorthem/ui/bar.h>
#include <sorthem/config.h>

#define STR_TO_BAR_HEIGHT_T(str) std::stof((str))

namespace sorthem {

class Graph : public sf::Drawable {
    sorthem::ContextVector<Bar> m_bars;
    std::vector<bar_height_t> m_initial_data;
    // Points to the view of the window
    const sf::View* m_win_view;
    bar_height_t m_max_height;
    std::stack<context_t> m_context_stack;

  public:
    Graph(const sf::View* win_view);

    /**
     * @brief Execute an operation on the sorting graph.
    */
    void execute(std::string operation);

    /**
     * @brief Initialize the bars and set their positions.
     *
     * This function should be called only once, when the window is created.
    */
    void loadRectsValues();

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
     * @brief Resets all the bar states to the default state and with their
     * default values
    */
    void resetBarStates();

    /**
     * @brief Refreshes all the bar states. No values are modified.
    */
    void refreshBarStates();

    /**
     * @brief To indicate that the animation has finished. This will set all the
     * bars to the default state, and will check if the sorting is correct.
    */
    void finishAnimation();

    /**
     * @brief Reads all the array data from the stdin and loads it into m_data.
     *
     * The data will be read from "[" to "]" and must have the form of:
     * [ 100 234 23 12.2 1.5 ]
     *
     * On finish, it updates all the graph.
    */
    void loadArrayDataFromStdin();

    /* Basic sorting operations (documentend on the README.md) */

    void swap(size_t index_a, size_t index_b);
    void compare(size_t index_a, size_t index_b);
    void set(size_t index, bar_height_t absolute_value);
    void get(size_t index);
    void set_mark(size_t index, std::string mark);
    void pushContext(size_t from, size_t to);
    void popContext();
};

}
