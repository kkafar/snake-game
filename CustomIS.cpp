#include "CustomIS.h"



CustomIS::CustomIS()
{
	buffer = Snake::Direction::NONE;
}


CustomIS::~CustomIS()
{
}

void CustomIS::setBuffer(Snake::Direction dir)
{
	buffer = dir;
}

void CustomIS::clear()
{
	buffer = Snake::Direction::NONE;
}

Snake::Direction CustomIS::getDirection()
{
	return buffer;
}