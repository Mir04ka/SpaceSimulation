#include <SFML/Graphics.hpp>
#include <vector>

#include "Object.h"
#include "MathSingleton.h"

MathSingleton* MathSingleton::instance = nullptr;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Space", sf::Style::Fullscreen, settings);
    
    MathSingleton& math = MathSingleton::getInstance();

    std::vector<Object> objects;

    objects.push_back(Object(sf::Vector2f(200, 500), 100, 300000000000, sf::Color::Blue));
    objects.push_back(Object(sf::Vector2f(550, 575), 25, 10000000000, sf::Color::Green));
    objects.push_back(Object(sf::Vector2f(1000, 550), 50, 200000000000, sf::Color::Red));

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

        //Force calculation and applying
        
        for (int it = 0; it < objects.size(); it++)
        {
            sf::Vector2f totalForce = sf::Vector2f(0.0, 0.0);

            for (int it2 = 0; it2 < objects.size(); it2++)
            {
                if (it != it2) totalForce += math.getForce(objects[it].getPosition(), objects[it2].getPosition(), objects[it].getMass(), objects[it2].getMass());
            }

            objects[it].update(totalForce, dt.asSeconds());
        }

        //Collision
        
        for (int it = 0; it < objects.size(); it++)
        {
            for (int it2 = 0; it2 < objects.size(); it2++)
            {
                if (it != it2 && math.isCollided(objects[it].getPosition(), objects[it2].getPosition(), objects[it].getRadius(), objects[it2].getRadius()))
                {
                    if (objects[it2].getRadius() > objects[it].getRadius())
                    {
                        objects[it2].setRadius(math.getRadius(objects[it].getRadius(), objects[it2].getRadius()));
                        objects.erase(objects.begin() + it);
                    }
                    else
                    {
                        objects[it].setRadius(math.getRadius(objects[it].getRadius(), objects[it2].getRadius()));
                        objects.erase(objects.begin() + it2);
                    }
                }
            }
        }
        
        //Drawing

        window.clear();

        for (int it = 0; it < objects.size(); it++)
        {
            window.draw(objects[it]);
        }

        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}