#include "Bar.h"

Bar::Bar() : m_shape() {}

sf::Vector2f Bar::getSize() {
    return m_shape.getSize();
}

void Bar::setSize(sf::Vector2f new_size) {
    m_shape.setSize(new_size);
}
void Bar::setPosition(sf::Vector2f new_pos) {
    m_shape.setPosition(new_pos);
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
