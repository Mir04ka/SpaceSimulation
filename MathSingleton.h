#pragma once
#include <SFML/Graphics.hpp>

class MathSingleton
{
public:
    static MathSingleton& getInstance();

    bool isCollided(sf::Vector2f pos1, sf::Vector2f pos2, float rad1, float rad2);
    
    sf::Vector2f getForce(sf::Vector2f pos1, sf::Vector2f pos2, float mas1, float mas2);

    MathSingleton(const MathSingleton&) = delete;
    MathSingleton& operator=(const MathSingleton&) = delete;

private:
    const float G = 6.6743 * pow(10, -11);

    MathSingleton() {};

    ~MathSingleton() {};

    static MathSingleton* instance;

    float getDistance(sf::Vector2f pos1, sf::Vector2f pos2);
};

