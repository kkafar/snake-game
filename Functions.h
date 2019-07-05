#pragma once
#include "Snake.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>

enum GAMESTATE { START = 0, STARTED = 1, ENDED = 2 };

void error(std::string s)
{
	std::cout << s << "\n";
}

void countModifiers(Snake::Direction dir, float sideLength, float outline, float &modifierX, float &modifierY)
{
	switch (dir)
	{
	case Snake::Direction::UP:
		modifierX = 0; 
		modifierY = (sideLength + outline);
		break;

	case Snake::Direction::DOWN:
		modifierX = 0; 
		modifierY = -(sideLength + outline);
		break;

	case Snake::Direction::LEFT:
		modifierX = (sideLength + outline);
		modifierY = 0;
		break;

	case Snake::Direction::RIGHT:
		modifierX = -(sideLength + outline);
		modifierY = 0; 
		break;

	default:
		error("Default in countModifiers(...) function");

	}
}

void printGrid(float width, float height, float distance, sf::RenderWindow& window, float thickness)
{
	sf::RectangleShape lineH, lineV;
	lineH.setSize({ width, thickness });
	lineV.setSize({ thickness, height });
	lineH.setFillColor(sf::Color::White);
	lineV.setFillColor(sf::Color::White);

	for (int i = 0; i < height / distance; ++i)
	{
		lineH.setPosition({ 0, i * distance });
		window.draw(lineH);
	}

	for (int i = 0; i < width / distance; ++i)
	{
		lineV.setPosition({ i * distance, 0 });
		window.draw(lineV);
	}
}

