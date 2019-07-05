#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <vector>


class Snake 
{

public:
	Snake(sf::Vector2f &position, float speed = 1, float width = 64, float height = 64);
	Snake();
	~Snake();

	enum Direction { LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, NONE = 4 };

	void setDirection(Direction);

	Direction getDirection();

	void drawTo(sf::RenderWindow&);

	void setPosition(const sf::Vector2f&);

	void moveHead();

	sf::Vector2f getPosition();

	void setColor(sf::Color);

	sf::RectangleShape getRect();

	bool isGameOver();


private:
	sf::RectangleShape rect;

	Direction direction;

	float movementSpeed;

	sf::Sprite sprite;

	int counter;

	bool isAlive;

};

