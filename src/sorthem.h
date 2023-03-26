#include <SFML/Graphics.hpp>

#define RECTS_NUMBER 100

class SorthemApp {
    sf::RenderWindow m_window;
    std::vector<sf::RectangleShape> m_rectangles;

public:
    SorthemApp(sf::VideoMode win_mode, sf::Uint32 style) :
        m_window(win_mode, "sorthem", style),
        m_rectangles(RECTS_NUMBER)
    {
        std::srand(std::time(0));
        constructRectangles(m_rectangles, RECTS_NUMBER, m_window.getView().getSize());
    }

    void mainLoop() {
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
            }

            m_window.clear();
            /* draw */
            for (auto& rect : m_rectangles) {
                m_window.draw(rect);
            }
            m_window.display();
        }
    }

private:
    void constructRectangles(std::vector<sf::RectangleShape> &rectangles, std::size_t count, sf::Vector2f win_size) {
        float rects_width = win_size.x / count;
        for (std::size_t i = 0; i < count; i++) {
            float random_height = (std::rand() % static_cast<int>(win_size.y)) + 1;
            rectangles[i].setSize({ rects_width, random_height });
            rectangles[i].setPosition({ i * rects_width, win_size.y - random_height });
            // rectangles[i].setFillColor(sf::Color::Red);
        }
    }

    void resizeRectangles(std::vector<sf::RectangleShape> &rectangles, sf::Vector2f old_win_size, sf::Vector2f new_win_size) {
        if (rectangles.size() == 0) return;
        float new_width = new_win_size.x / rectangles.size();
        for (std::size_t i = 0; i < rectangles.size(); i++) {
            sf::RectangleShape& rect = rectangles[i];
            float new_heigth = new_win_size.y * rect.getSize().y / old_win_size.y;
            rect.setSize({ new_width, new_heigth });
            rect.setPosition({ i * new_width, new_win_size.y - new_heigth });
        }
    }
};
