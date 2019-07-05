#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>

class Rectangle
{
public:
	Rectangle(float sideLength, int tilesHorizontally, int tilesVertically, sf::Color color = sf::Color::Blue);
	~Rectangle();

	void setRandomPosition();

	void drawTo(sf::RenderWindow &);

	sf::RectangleShape getRect();

private:
	int sideLength, tilesH, tilesV;
	sf::RectangleShape rect;

};

