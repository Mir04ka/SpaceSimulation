#include "Object.h"
#include <iostream>

Object::Object(sf::Vector2f pos, float rad, float mas, sf::Color clr)
{
	shape.setRadius(rad);
	shape.setFillColor(clr);
	shape.setOrigin(rad, rad);
	shape.setPosition(pos);

	line.setSize(sf::Vector2f(rad + 3, 6));
	line.setFillColor(sf::Color::White);
	line.setOrigin(sf::Vector2f(3, 3));
	line.setPosition(pos);

	mass = mas;
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(line, states);
}

void Object::update(sf::Vector2f force, float dt)
{
	velocity += force / mass;

	shape.setPosition((shape.getPosition() + sf::Vector2f(velocity.x * dt, velocity.y * dt)));
}

sf::CircleShape Object::getShape()
{
	return shape;
}

void Object::setMass(float m)
{
	mass = m;
}

float Object::getMass()
{
	return mass;
}

void Object::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
}

sf::Vector2f Object::getPosition()
{
	return shape.getPosition();
}