#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Bar : public sf::Drawable {
  public:
    enum class state : short;
  private:
    sf::RectangleShape m_shape;
    state m_state;
    bool m_with_mark = false;
    std::string m_mark;
  public:
    inline static sf::Color default_color = sf::Color::White;
    Bar();

    void setSize(sf::Vector2f new_size);
    sf::Vector2f getSize();

    void setPosition(sf::Vector2f new_pos);
    sf::Vector2f getPosition();

    void setColor(sf::Color color);
    void setState(Bar::state state);

    std::string getMark();
    void setMark(std::string mark);

    void refreshState();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    enum class state : short {
        Iddle = 0,
        Swapping,
        Getting,
        Setting,
        Comparing,

        Count
    };
};
