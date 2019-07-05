#pragma once
#include <SFML\Graphics.hpp>
#include "Snake.h"
class CustomIS
{
public:
	CustomIS();
	~CustomIS();

	void setBuffer(Snake::Direction);

	void clear();

	Snake::Direction getDirection();

private:
	Snake::Direction buffer;

	
};

