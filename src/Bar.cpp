#include <SFML/Graphics.hpp>
#include "Bar.h"

Bar::Bar() : m_shape() {
    m_shape.setFillColor(m_default_color);
}

void Bar::setSize(sf::Vector2f new_size) {
    m_shape.setSize(new_size);
}
sf::Vector2f Bar::getSize() {
    return m_shape.getSize();
}

void Bar::setPosition(sf::Vector2f new_pos) {
    m_shape.setPosition(new_pos);
}
sf::Vector2f Bar::getPosition() {
    return m_shape.getPosition();
}

void Bar::setColor(sf::Color color) {
    m_shape.setFillColor(color);
}

void Bar::setState(Bar::state state) {
    switch (state) {
    case Bar::state::Swapping: {
        m_shape.setFillColor(sf::Color::Red);
        break;
    }
    default:
        break;
    }
}

void Bar::refreshState() {
    switch (m_state) {
    case Bar::state::Swapping: {
        m_shape.setFillColor(m_default_color);
        break;
    }
    default:
        break;
    }
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
