#include "MathSingleton.h"

MathSingleton& MathSingleton::getInstance()
{
    if (!instance) {
        instance = new MathSingleton();
    }
    return *instance;
}

bool MathSingleton::isCollided(sf::Vector2f pos1, sf::Vector2f pos2, float rad1, float rad2)
{
    return (getDistance(pos1, pos2) <= rad1 || getDistance(pos1, pos2) <= rad2);
}

sf::Vector2f MathSingleton::getForce(sf::Vector2f pos1, sf::Vector2f pos2, float mas1, float mas2)
{
    sf::Vector2f forceVector = (pos2 - pos1);
    float forceScalar = ((G * mas1 * mas2) / pow(getDistance(pos1, pos2), 2));

    return forceVector * forceScalar;
}

float MathSingleton::getRadius(float r1, float r2)
{
    return (sqrt((pow(r1, 2) + pow(r2, 2))));
}

float MathSingleton::getDistance(sf::Vector2f pos1, sf::Vector2f pos2)
{
    return sqrt(pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2));
}