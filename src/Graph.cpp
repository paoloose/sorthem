#include <vector>
#include <iostream>
#include <sstream>
#include <thread>
#include <string>
#include <cstring>
#include "Graph.h"

Graph::Graph(int bars_number, const sf::View* win_view) :
    m_bars(bars_number),
    m_win_view(win_view)
{ }

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
    else if (command == "compare") {
        long int a, b;
        iss >> a >> b;
        if (iss.fail()) {
            throw std::runtime_error("error executing compare command: " + operation);
        }
        // check for index out of range
        if (a < 0 || b < 0) {
            throw std::runtime_error("compare: out of range");
        }

        this->compare(static_cast<size_t>(a), static_cast<size_t>(b));
    }
    else if (command == "set") {
        long int a, b;
        iss >> a >> b;
        if (iss.fail()) {
            throw std::runtime_error("error executing set command: " + operation);
        }
        // check for index out of range
        if (a < 0 || b < 0) {
            throw std::runtime_error("set: out of range");
        }

        this->set(static_cast<size_t>(a), static_cast<size_t>(b));
    }
    else if (command == "get") {
        long int a;
        iss >> a;
        if (iss.fail()) {
            throw std::runtime_error("error executing get command: " + operation);
        }
        // check for index out of range
        if (a < 0) {
            throw std::runtime_error("get: out of range");
        }

        this->get(static_cast<size_t>(a));
    }
    else if (command == "mark") {
        long int a;
        iss >> a;
        if (iss.fail()) {
            throw std::runtime_error("error executing mark command: " + operation);
        }

        std::string mark;
        iss >> mark;
        if (mark != "as") {
            throw std::runtime_error("error: bad syntax. expected: mark <i> as <name>, got: " + operation);
        }

        iss >> mark;
        for (auto& bar : m_bars) {
            if (bar.getMark() == mark) {
                bar.setMark("");
            }
        }

        this->set_mark(static_cast<size_t>(a), mark);
    }
    else {
        std::cout << "unknown operation: " << operation << "\n";
    }
}

void Graph::constructRectangles(sf::Vector2f win_size) {
    size_t count = m_bars.size();
    float rects_width = win_size.x / count;
    for (std::size_t i = 0; i < count; i++) {
        float random_height = (std::rand() % static_cast<int>(win_size.y)) + 1;
        m_bars[i].setSize({ rects_width, random_height });
        m_bars[i].setPosition({ i * rects_width, win_size.y - random_height });
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

void Graph::loadDataFromProcessThread(FILE* pipe, bool* loading) {
    char buffer[256];
    // The string where the complete array representation will be loaded
    std::string str_arr;
    bool array_started = false;
    bool array_closed  = false;

    /* Load the date from the pipe */

    // Read until we find a "]" or the end of the pipe
    // Note that:
    // - fgets already adds the null terminator
    // - fgets stops reading when it finds a new line, EOF or the buffer is full
    while (!array_closed && (fgets(buffer, sizeof(buffer), pipe) != nullptr)) {
        std::string str(buffer);
        for (size_t i = 0; i < str.length(); i++) {
            if (buffer[i] == '[') {
                if (array_started) {
                    throw std::runtime_error("load: bad start of array");
                }
                array_started = true;
                continue;
            }
            if (buffer[i] == ']') {
                if (!array_started) {
                    throw std::runtime_error("load: bad end of array");
                }
                array_closed = true;
                break;
            }

            if (array_started) {
                str_arr += buffer[i];
            }
        }
    }

    if (!array_closed) {
        throw std::runtime_error("load: couldn't find end of array");
    }

    /* Parse the data into a vector */
    // str_arr is like "[ 100 234 23 12.2 1.5 ]";

    std::vector<bar_height_t> nums;
    // We use string streams to parse the data *easily*
    std::istringstream iss(str_arr);
    std::string str_num;

    std::cout << "str_arr: " << str_arr << "\n";

    while (iss >> str_num) {
        std::cout << "token: " << str_num << "\n";
        try {
            bar_height_t num = STR_TO_BAR_HEIGHT_T(str_num);
            nums.push_back(num);
        }
        catch (...) {
            // TODO: handle exceptions better (with UI)
            throw std::runtime_error("load: bad number: " + str_num + ".");
        }
    }

    /* Refresh the bars */

    m_max_height = *std::max_element(nums.begin(), nums.end());
    size_t count = nums.size();
    m_bars.resize(count);
    float rects_width = m_win_view->getSize().x / static_cast<float>(count);
    for (std::size_t i = 0; i < count; i++) {
        float height = nums[i] / m_max_height * m_win_view->getSize().y;
        m_bars[i].setSize({ rects_width, height });
        m_bars[i].setPosition({ i * rects_width, m_win_view->getSize().y - height });
    }

    *loading = false;
    std::cout << "load: finished loading data\n";

    // Read the remaining data from the pipe
    // this is to avoid to send a SIGPIPE signal to the child process
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        // do nothing
    }
    std::cout << "load: finished reading remaining data\n";
    pclose(pipe);
}

/* Sorting operations */

void Graph::swap(size_t index_a, size_t index_b) {
    size_t bars_num = m_bars.size();
    if (index_a >= bars_num || index_b >= bars_num) {
        throw std::runtime_error("swap: out of range");
    }

    Bar &bar_a = m_bars[index_a];
    Bar &bar_b = m_bars[index_b];

    sf::Vector2f bar_a_pos = bar_a.getPosition();
    sf::Vector2f bar_b_pos = bar_b.getPosition();
    bar_a.setPosition({ bar_b_pos.x, bar_a_pos.y });
    bar_b.setPosition({ bar_a_pos.x, bar_b_pos.y });
    // colorize
    bar_a.setState(Bar::state::Swapping);
    bar_b.setState(Bar::state::Swapping);
    std::swap(bar_a, bar_b);
}

void Graph::compare(size_t index_a, size_t index_b) {
    size_t bars_num = m_bars.size();
    if (index_a >= bars_num || index_b >= bars_num) {
        throw std::runtime_error("compare: out of range");
    }

    Bar &bar_a = m_bars[index_a];
    Bar &bar_b = m_bars[index_b];

    // colorize
    bar_a.setState(Bar::state::Comparing);
    bar_b.setState(Bar::state::Comparing);
}

void Graph::set(size_t index, bar_height_t value) {
    size_t bars_num = m_bars.size();
    if (index >= bars_num) {
        throw std::runtime_error("set: out of range");
    }

    Bar &bar = m_bars[index];
    bar_height_t relative_height = value * m_win_view->getSize().y / m_max_height;

    bar.setSize({ bar.getSize().x, relative_height });
    bar.setPosition({ bar.getPosition().x, m_win_view->getSize().y - relative_height });

    bar.setState(Bar::state::Setting);
}

void Graph::get(size_t index) {
    size_t bars_num = m_bars.size();
    if (index >= bars_num) {
        throw std::runtime_error("get: out of range");
    }
    // Just colorize the bar
    m_bars[index].setState(Bar::state::Getting);
}

void Graph::set_mark(size_t index, std::string mark) {
    size_t bars_num = m_bars.size();
    if (index >= bars_num) {
        throw std::runtime_error("set_mark: out of range");
    }

    for (size_t i = 0; i < bars_num; i++) {
        m_bars[i].setMark("");
    }
    // Just colorize the bar
    m_bars[index].setMark(mark);
}
