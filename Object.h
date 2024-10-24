#pragma once
#include <SFML/Graphics.hpp>

class Object : public sf::Drawable
{
private:
	sf::Vector2f position = sf::Vector2f(0.0, 0.0);
	sf::Vector2f velocity = sf::Vector2f(0.0, 0.0);
	sf::Vector2f acceleration = sf::Vector2f(0.0, 0.0);
	float radius = 1.0;
	float mass = 1.0;

	sf::Color color = sf::Color::Blue;

	sf::CircleShape shape;
	sf::RectangleShape line;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Object(sf::Vector2f pos, float rad, float mas, sf::Color clr);
	
	Object(sf::Vector2f pos, sf::Vector2f vel, float rad, float mas, sf::Color clr);

	virtual ~Object() {};

	void update(sf::Vector2f force, float dt);

	sf::CircleShape getShape();

	void setMass(float m);

	float getMass();

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void setRadius(float r);

	float getRadius();

	void setColor(sf::Color cl);

	sf::Color getColor();

	void setVelocity(sf::Vector2f vel);

	sf::Vector2f getVelocity();
};