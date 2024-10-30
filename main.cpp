#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "Object.h"
#include "MathSingleton.h"
#include "CursorSingleton.h"

#define WHEEL_K 0.5
#define MIN_SCALE 0.1
#define CAMERA_SPEED 500

MathSingleton* MathSingleton::instance = nullptr;
CursorSingleton* CursorSingleton::instance = nullptr;

sf::View view(sf::Vector2f(960.f, 540.f), sf::Vector2f(1920.f, 1080.f)); // Camera creating

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Space", sf::Style::Fullscreen, settings);
    
    const sf::Vector2f defaultCameraSize = sf::Vector2f(1920.f, 1080.f);

    MathSingleton& math = MathSingleton::getInstance();
    CursorSingleton& cursor = CursorSingleton::getInstance();

    std::vector<Object> objects;
    /*
    objects.push_back(Object(sf::Vector2f(200, 00), 100, 3000000000000, sf::Color::Blue));
    objects.push_back(Object(sf::Vector2f(550, 575), 25, 10000000000, sf::Color::Green));
    objects.push_back(Object(sf::Vector2f(1000, 1000), 50, 200000000000, sf::Color::Red));
    objects.push_back(Object(sf::Vector2f(1500, 300), sf::Vector2f(00, 00), 200, 3000000000000, sf::Color::Yellow));
    */

    float camaraScale = 1;
    bool wasPressed = false;

    sf::Clock deltaClock;
    sf::Time dt = deltaClock.restart();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Input
        
        cursor.setPosition(math.getGlobalPos(view.getCenter(), view.getSize(), sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)));
        Object newObject = cursor.update(sf::Mouse::getPosition(), event, dt.asSeconds());

        if (newObject.isReal())
        {
            newObject.setPosition(math.getGlobalPos(view.getCenter(), view.getSize(), sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)));
            objects.push_back(newObject);
        }
        /*
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (!wasPressed)
            {
                objects.push_back(Object(math.getGlobalPos(view.getCenter(), view.getSize(), sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)), 10, 30000000000, sf::Color::Blue));
                wasPressed = true;
            }
        }
        else
        {
            wasPressed = false;
        }*/
        /*
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and sf::Mouse::Wheel::HorizontalWheel)
        {
            cursor.setOutlineColor(sf::Color::Red);
        }
        */
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            camaraScale -= event.mouseWheelScroll.delta * WHEEL_K * dt.asSeconds();

            if (camaraScale < MIN_SCALE) camaraScale = MIN_SCALE;

            view.setSize(defaultCameraSize * camaraScale);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            view.move(0, -CAMERA_SPEED * dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            view.move(-CAMERA_SPEED * dt.asSeconds(), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            view.move(0, CAMERA_SPEED * dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            view.move(CAMERA_SPEED * dt.asSeconds(), 0);
        }

        cursor.setPosition(math.getGlobalPos(view.getCenter(), view.getSize(), sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)));

        // Force calculation and applying
        
        for (int it = 0; it < objects.size(); it++)
        {
            sf::Vector2f totalForce = sf::Vector2f(0.0, 0.0);

            for (int it2 = 0; it2 < objects.size(); it2++)
            {
                if (it != it2) totalForce += math.getForce(objects[it].getPosition(), objects[it2].getPosition(), objects[it].getMass(), objects[it2].getMass());
            }

            objects[it].update(totalForce, dt.asSeconds());
        }

        // Collision
        
        for (int it = 0; it < objects.size(); it++)
        {
            for (int it2 = 0; it2 < objects.size(); it2++)
            {
                if (it != it2 && math.isCollided(objects[it].getPosition(), objects[it2].getPosition(), objects[it].getRadius(), objects[it2].getRadius()))
                {
                    if (objects[it2].getRadius() > objects[it].getRadius())
                    {
                        objects.push_back(Object(objects[it2].getPosition(), math.getVelocity(objects[it].getVelocity(), objects[it2].getVelocity(), objects[it].getMass(), objects[it2].getMass()), math.getRadius(objects[it].getRadius(), objects[it2].getRadius()), objects[it].getMass() + objects[it2].getMass(), objects[it2].getColor()));
                    }
                    else
                    {
                        objects.push_back(Object(objects[it].getPosition(), math.getVelocity(objects[it].getVelocity(), objects[it2].getVelocity(), objects[it].getMass(), objects[it2].getMass()), math.getRadius(objects[it].getRadius(), objects[it2].getRadius()), objects[it].getMass() + objects[it2].getMass(), objects[it].getColor()));
                    }

                    objects[it] = objects.back();
                    objects.pop_back();
                    objects[it2] = objects.back();
                    objects.pop_back();
                }
            }
        }
        
        // Drawing

        window.clear();
        window.setView(view);

        for (int it = 0; it < objects.size(); it++)
        {
            window.draw(objects[it]);
        }

        window.draw(cursor);

        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}