#pragma once
#include <SFML/Graphics.hpp>

class Bar : public sf::Drawable {
    sf::RectangleShape m_shape;
  public:
    Bar();
    sf::Vector2f getSize();
    void setSize(sf::Vector2f new_size);
    void setPosition(sf::Vector2f new_pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
