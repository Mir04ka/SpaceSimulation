#pragma once
#include <SFML/Graphics.hpp>

#include "Object.h"

class CursorSingleton : public sf::Drawable
{
public:
    static CursorSingleton& getInstance();

    CursorSingleton(const CursorSingleton&) = delete;
    CursorSingleton& operator=(const CursorSingleton&) = delete;

    Object update(sf::Vector2i mousePos, sf::Event currentEvent, float dt);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    void setPosition(sf::Vector2f newPos);

private:
    sf::Vector2f setPos;
    bool wasPressed = false;

    sf::CircleShape shape = sf::CircleShape(30);

    CursorSingleton();

    ~CursorSingleton() {};

    static CursorSingleton* instance;
};

