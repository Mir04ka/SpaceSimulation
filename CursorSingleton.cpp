#include "CursorSingleton.h"
#include <iostream>

CursorSingleton::CursorSingleton()
{
    shape.setRadius(30);
    shape.setOrigin(sf::Vector2f(30, 30));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(2);
}

CursorSingleton& CursorSingleton::getInstance()
{
    if (!instance) {
        instance = new CursorSingleton();
    }
    return *instance;
}

Object CursorSingleton::update(sf::Vector2i mousePos, sf::Event currentEvent, float dt)
{
    shape.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);

    if (currentEvent.type == sf::Event::MouseButtonPressed and currentEvent.mouseButton.button == sf::Mouse::Left)
    {
        if (not wasPressed)
        {
            wasPressed = true;

            setPos = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
        }
    }

    if (currentEvent.type == sf::Event::MouseButtonReleased and currentEvent.mouseButton.button == sf::Mouse::Left)
    {
        if (not wasPressed)
        {
            wasPressed = true;

            return Object(sf::Vector2f(), shape.getRadius(), 30000000000, sf::Color::Green);
        }
    }
    else
    {
        wasPressed = false;
    }

    return Object();
}

void CursorSingleton::setPosition(sf::Vector2f newPos)
{
    shape.setPosition(newPos);
}

void CursorSingleton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(shape, states);
}