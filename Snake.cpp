#include "Snake.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

Snake::Snake()
{
	rect.setSize({ 64, 64 });
}

Snake::Snake(sf::Vector2f &position, float speed, float width, float height) :
	movementSpeed(speed)
{
	rect.setPosition(position);
	rect.setSize({ width, height });
	rect.setFillColor(sf::Color::Green);
	rect.setOutlineThickness(-2);
	rect.setOutlineColor(sf::Color::Black);
	counter = 0; 
	direction = UP;
	isAlive = true;
}

Snake::~Snake()
{
	std::cout << "Object of the SNAKE class has been destroyed\n";
}

void Snake::setDirection(Direction dir)
{
	direction = dir;
}

void Snake::drawTo(sf::RenderWindow &window)
{
	window.draw(rect);
}

void Snake::setPosition(const sf::Vector2f &pos)
{
	rect.setPosition(pos);
}

void Snake::moveHead()
{
	switch (direction)
	{
	case LEFT:
		rect.move(-movementSpeed, 0);
		break;

	case RIGHT:
		rect.move(movementSpeed, 0);
		break;

	case UP:
		rect.move(0, -movementSpeed);
		break;

	case DOWN: 
		rect.move(0, movementSpeed);
		break;

	case NONE:
		break;

	default:
		std::cout << "Default in Snake::moveHead() function\n";
	}	
}

Snake::Direction Snake::getDirection()
{
	return direction;
}

sf::Vector2f Snake::getPosition()
{
	return rect.getPosition();
}

void Snake::setColor(sf::Color color)
{
	rect.setFillColor(color);
}

sf::RectangleShape Snake::getRect()
{
	return rect;
}

bool Snake::isGameOver()
{
	return !isAlive;
}