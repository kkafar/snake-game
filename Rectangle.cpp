#include "Rectangle.h"
#include <iostream>

Rectangle::Rectangle(float sideL, int tH, int tV, sf::Color color) :
	sideLength(sideL),
	tilesH(tH),
	tilesV(tV)
{
	rect.setSize({ (sideL), (sideL) });
	rect.setFillColor(color);
}


Rectangle::~Rectangle()
{
	std::cout << "Object of the Rectangle class has been destroyed!\n";
}

void Rectangle::setRandomPosition()
{
	rect.setPosition(sf::Vector2f((rand() % tilesH) * sideLength, (rand() % tilesV) * sideLength));
}

void Rectangle::drawTo(sf::RenderWindow &window)
{
	window.draw(rect);
}

sf::RectangleShape Rectangle::getRect()
{
	return rect;
}