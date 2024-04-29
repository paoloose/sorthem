#include <SFML/Graphics.hpp>
#include <iostream>
#include <sorthem/ui/bar.h>
#include <sorthem/config.h>

sorthem::Bar::Bar() : m_shape(), m_state(Bar::state::Iddle) {
    m_shape.setFillColor(Bar::default_color);
}

void sorthem::Bar::setSize(sf::Vector2f new_size) {
    m_shape.setSize(new_size);
}
sf::Vector2f sorthem::Bar::getSize() {
    return m_shape.getSize();
}

void sorthem::Bar::setPosition(sf::Vector2f new_pos) {
    m_shape.setPosition(new_pos);
}
sf::Vector2f sorthem::Bar::getPosition() {
    return m_shape.getPosition();
}

void sorthem::Bar::setColor(sf::Color color) {
    m_shape.setFillColor(color);
}

std::string sorthem::Bar::getMark() {
    return m_mark;
}
void sorthem::Bar::setMark(std::string mark) {
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

void sorthem::Bar::setState(Bar::state state) {
    if (m_with_mark) return;

    m_state = state;
    switch (m_state) {
    case Bar::state::InContext: {
        m_shape.setFillColor(Bar::context_color);
        break;
    }
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

void sorthem::Bar::refreshState() {
    if (m_with_mark) return;

    switch (m_state) {
    case Bar::state::Swapping:
    case Bar::state::Getting:
    case Bar::state::Setting:
    case Bar::state::Comparing: {
        setState(Bar::state::Iddle);
        break;
    }
    default:
        break;
    }
}

void sorthem::Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
