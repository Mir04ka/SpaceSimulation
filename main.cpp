#include <SFML/Graphics.hpp>
#include <list>

#include "Object.h"
#include "MathSingleton.h"

MathSingleton* MathSingleton::instance = nullptr;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Space", sf::Style::Fullscreen, settings);
    
    MathSingleton& math = MathSingleton::getInstance();

    std::list<Object*> objects;
    std::list<Object*>::iterator it;
    std::list<Object*>::iterator it2;

    objects.push_back(new Object(sf::Vector2f(1000, 500), 100, 300000000000, sf::Color::Blue));
    objects.push_back(new Object(sf::Vector2f(1025, 575), 25, 10000000000, sf::Color::Green));
    objects.push_back(new Object(sf::Vector2f(1000, 550), 50, 200000000000, sf::Color::Red));

    Object ojb = Object(sf::Vector2f(500, 550), 50, 200000000000, sf::Color::Yellow);

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
        
        for (it = objects.begin(); it != objects.end(); it++)
        {
            sf::Vector2f totalForce = sf::Vector2f(0.0, 0.0);

            for (it2 = objects.begin(); it2 != objects.end(); it2++)
            {
                if ((*it) != (*it2)) totalForce += math.getForce((*it)->getPosition(), (*it2)->getPosition(), (*it)->getMass(), (*it2)->getMass());
            }

            (*it)->update(totalForce, dt.asSeconds());
        }

        //Collision
        /*
        for (it = objects.begin(); it != objects.end(); it++)
        {
            for (it2 = objects.begin(); it2 != objects.end(); it2++)
            {
                if ((*it) != (*it2) && math.isCollided((*it)->getPosition(), (*it2)->getPosition(), (*it)->getMass(), (*it2)->getMass()))
                {
                    objects.remove((*it));
                }
            }
        }
        */
        //Drawing

        window.clear();

        for (it = objects.begin(); it != objects.end(); it++)
        {
            window.draw((*it)->getShape());
        }

        window.display();
        dt = deltaClock.restart();
    }

    return 0;
}