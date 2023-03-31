#pragma once
#include <SFML/Graphics.hpp>

class Bar : public sf::Drawable {
  public:
    enum class state : short;
  private:
    sf::RectangleShape m_shape;
    state m_state;
    sf::Color m_default_color = sf::Color::White;
  public:
    Bar();

    void setSize(sf::Vector2f new_size);
    sf::Vector2f getSize();

    void setPosition(sf::Vector2f new_pos);
    sf::Vector2f getPosition();

    void setColor(sf::Color color);

    void setState(Bar::state state);

    void refreshState();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    enum class state : short {
        Swapping = 0,
        Getting,
        Setting,
        Comparing,

        count
    };
};
