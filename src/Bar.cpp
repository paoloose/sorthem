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

std::string Bar::getMark() {
    return m_mark;
}
void Bar::setMark(std::string mark) {
    if (mark != "") {
        m_mark = mark;
        m_with_mark = true;
        m_shape.setFillColor(sf::Color(255, 165, 0));
    }
    else {
        m_mark = "";
        m_with_mark = false;
        setState(Bar::state::Iddle);
    }
}

void Bar::setState(Bar::state state) {
    if (m_with_mark) return;

    m_state = state;
    switch (m_state) {
    case Bar::state::Iddle: {
        m_shape.setFillColor(Bar::default_color);
        break;
    }
    case Bar::state::Swapping: {
        m_shape.setFillColor(Bar::swapping_color);
        break;
    }
    case Bar::state::Getting: {
        m_shape.setFillColor(Bar::getting_color);
        break;
    }
    case Bar::state::Setting: {
        m_shape.setFillColor(Bar::setting_color);
        break;
    }
    case Bar::state::Comparing: {
        m_shape.setFillColor(Bar::comparing_color);
        break;
    }
    default:
        break;
    }
}

void Bar::refreshState() {
    if (m_with_mark) return;

    switch (m_state) {
    case Bar::state::Iddle: {
        break;
    }
    case Bar::state::Swapping: {
        setState(Bar::state::Iddle);
        break;
    }
    case Bar::state::Getting: {
        setState(Bar::state::Iddle);
        break;
    }
    case Bar::state::Setting: {
        setState(Bar::state::Iddle);
        break;
    }
    case Bar::state::Comparing: {
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
