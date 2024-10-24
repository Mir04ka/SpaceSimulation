#include "Object.h"
#include <iostream>

Object::Object(sf::Vector2f pos, float rad, float mas, sf::Color clr)
{
	shape.setRadius(rad);
	shape.setFillColor(clr);
	shape.setOrigin(rad, rad);
	shape.setPosition(pos);

	line.setSize(sf::Vector2f(rad + 2, 4));
	line.setFillColor(sf::Color::White);
	line.setOrigin(sf::Vector2f(2, 2));
	line.setPosition(pos);

	mass = mas;
}

Object::Object(sf::Vector2f pos, sf::Vector2f vel, float rad, float mas, sf::Color clr)
{
	shape.setRadius(rad);
	shape.setFillColor(clr);
	shape.setOrigin(rad, rad);
	shape.setPosition(pos);

	line.setSize(sf::Vector2f(rad, 4));
	line.setFillColor(sf::Color::White);
	line.setOrigin(sf::Vector2f(2, 2));
	line.setPosition(pos);

	mass = mas;
	velocity = vel;
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
	line.setPosition((shape.getPosition() + sf::Vector2f(velocity.x * dt, velocity.y * dt)));
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

void Object::setRadius(float r)
{
	sf::Vector2f oldPos = shape.getPosition();
	float oldRad = shape.getRadius();

	shape.setRadius(r);
	shape.setPosition(shape.getPosition() + sf::Vector2f((r - oldRad) / 2, (r - oldRad) / 2));
	line.setSize(sf::Vector2f(r + 2, 4));
	line.setPosition(sf::Vector2f((r - oldRad) / 2, (r - oldRad) / 2));
}

float Object::getRadius()
{
	return shape.getRadius();
}

void Object::setColor(sf::Color cl)
{
	shape.setFillColor(cl);
}

sf::Color Object::getColor()
{
	return shape.getFillColor();
}

void Object::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

sf::Vector2f Object::getVelocity()
{
	return velocity;
}