#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bar.h"

Bar::Bar() : m_shape(), m_state(Bar::state::Iddle) {
    m_shape.setFillColor(Bar::default_color);
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
    m_state = state;
    switch (m_state) {
    case Bar::state::Iddle: {
        m_shape.setFillColor(Bar::default_color);
        break;
    }
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
        setState(Bar::state::Iddle);
        break;
    }
    default:
        break;
    }
}

void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
