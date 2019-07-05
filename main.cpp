#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <conio.h>
#include "Snake.h"
#include <vector>
#include "Functions.h"
#include <iostream>
#include <time.h>
#include "Rectangle.h"
#include <string>
#include "CustomIS.h"
using namespace std;
using namespace sf;

/* 

*/



int main()
{	
	// wykorzystujemy do generowania losowej pozycji klocka który 
	// jest celem dla wê¿a
	srand(time(NULL));
	
	// timeAsSec - czas po jakim nastêpuje kolejne obliczenie pozycji wszytkich obiektów na 
	// ekranie, im mniejsza wartoœæ tym szybiej chodzi gra
	const float timeAsSec = 0.15;

	// zmienna odzwierciedlaj¹ca stan w którym obecnie znajduje siê rozgrywka
	GAMESTATE gamestate = START;

	// modyfikatory wykorzystywane do oblicznia pozycji "dok³adanych" do wê¿a 
	// klocków (po wciœniêciu S lub po zjedzeniu klocka)
	float modifierX = 0, modifierY = 0;

	// przechowuje ostatni za¿¹dany przez gracza kierunek
	CustomIS directionBuffer;

	// zmienne czasowe
	// 1: zmiana kiernku "g³owy"
	// 2: poruszenie ca³ym wê¿em, aktualizacja kierunku pozosta³ych (prócz g³owy),
	// 3: kolizja 
	// 4: wyœwietlanie siatki
	Clock clock, clock2, clock3, clock4;
	Time time, time2, time3, time4;

	// do wyœwietlania score:
	Text text, gridMessage, startMessage, endMessage;
	Font font;
	
	if (!font.loadFromFile("arial.ttf"))
		error("font error");


	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);
	text.setPosition({ 0, 0 });
	gridMessage.setFont(font);
	gridMessage.setCharacterSize(16);
	gridMessage.setFillColor(sf::Color::White);
	gridMessage.setPosition({ 500, 0 });
	gridMessage.setString("Press \"G\" to turn ON the grid!");
	startMessage.setFont(font);
	startMessage.setCharacterSize(32);
	startMessage.setFillColor(sf::Color::White);
	startMessage.setPosition({ 182, 250 });
	startMessage.setString("Press \"Space\" to start the game!");
	endMessage.setFont(font);
	endMessage.setCharacterSize(32);
	endMessage.setFillColor(sf::Color::White);
	endMessage.setPosition({ 182, 250 });
	


	// zmienna przechowuj¹ca aktualny wynik gracza
	int score = 0;
	text.setString("Score: " + to_string(score));
	
	//H - horizontally, V - vertically
	int numbOfRecTilesH, numbOfRecTilesV;
	
	// false - nie wyœwietlamy siatki
	bool grid = false;


	RenderWindow game(VideoMode(800, 608), "GAME", Style::Default);
	game.setFramerateLimit(60);


	// number of tiles our snake is made of
	unsigned int snakeSize = 0;

	int sideLength = 32;

	// sideLength should divide both dimensions of the game's widnow.
	// they should be multiples of 32;
	numbOfRecTilesH = game.getSize().x / sideLength;
	numbOfRecTilesV = game.getSize().y / sideLength;

	// g³owa wê¿a. Snake(sf::Vector2f &position, float speed = 1, float width = 64, float height = 64);
	Snake snakeTile(sf::Vector2f(game.getSize().x / 2 - sideLength / 2 , game.getSize().y / 2 - sideLength / 2), sideLength, sideLength, sideLength);
	vector<Snake>snakeTileVector;

	// obiekt reprezentuj¹cy kostkê "do zjedzenia"
	Rectangle rect(sideLength, numbOfRecTilesH, numbOfRecTilesV);
	rect.setRandomPosition();

	// wrzucmy g³owê wê¿a do wektora
	snakeTileVector.push_back(snakeTile);

	// ustawianie 2 p³ytki
	snakeTile.setDirection(snakeTileVector[0].getDirection());
	countModifiers(snakeTileVector[0].getDirection(), sideLength, 0, modifierX, modifierY);
	snakeTile.setPosition(sf::Vector2f(snakeTileVector[0].getPosition().x + modifierX, snakeTileVector[0].getPosition().y + modifierY));
	snakeTileVector.push_back(snakeTile);

	snakeTileVector[0].setColor(sf::Color::Yellow);

	// bo na starcie sk³ada siê z 2 p³ytek
	snakeSize = 2;

	// g³ówna pêtla
	while (game.isOpen())
	{
		Event event;

		while (game.pollEvent(event))
		{ 
			// wyjœcie z gry
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				game.close();


			if (gamestate == STARTED)
			{
				time4 = clock4.getElapsedTime();
				if (Keyboard::isKeyPressed(Keyboard::G) && time4.asSeconds() > 0.5)
				{
					if (grid)
					{
						grid = false;
						gridMessage.setString("Press \"G\" to turn ON the grid!");
					}
					else
					{
						grid = true;
						gridMessage.setString("Press \"G\" to turn OFF the grid!");
					}
					clock4.restart();
				}


				// kierunek od gracza pobieramy z mo¿liwie najwiêksz¹ czêstotliwoœci¹
				// ale realizujemy go tylko raz na okreœlony czas
				if (Keyboard::isKeyPressed(Keyboard::Up))
					directionBuffer.setBuffer(Snake::Direction::UP);

				if (Keyboard::isKeyPressed(Keyboard::Down))
					directionBuffer.setBuffer(Snake::Direction::DOWN);

				if (Keyboard::isKeyPressed(Keyboard::Left))
					directionBuffer.setBuffer(Snake::Direction::LEFT);

				if (Keyboard::isKeyPressed(Keyboard::Right))
					directionBuffer.setBuffer(Snake::Direction::RIGHT);

				// sterowanie g³ow¹
				time = clock.getElapsedTime();
				if (time.asSeconds() > timeAsSec)
				{
					// druga czêœæ warunku, aby nie móc zawróciæ o 180 stopni
					if (directionBuffer.getDirection() == Snake::Direction::UP && snakeTileVector[0].getDirection() != Snake::Direction::DOWN)
					{
						clock.restart();
						snakeTileVector[0].setDirection(Snake::Direction::UP);
						directionBuffer.clear();
					}

					else if (directionBuffer.getDirection() == Snake::Direction::LEFT && snakeTileVector[0].getDirection() != Snake::Direction::RIGHT)
					{
						clock.restart();
						snakeTileVector[0].setDirection(Snake::Direction::LEFT);
						directionBuffer.clear();
					}

					else if (directionBuffer.getDirection() == Snake::Direction::RIGHT && snakeTileVector[0].getDirection() != Snake::Direction::LEFT)
					{
						clock.restart();
						snakeTileVector[0].setDirection(Snake::Direction::RIGHT);
						directionBuffer.clear();
					}

					else if (directionBuffer.getDirection() == Snake::Direction::DOWN && snakeTileVector[0].getDirection() != Snake::Direction::UP)
					{
						clock.restart();
						snakeTileVector[0].setDirection(Snake::Direction::DOWN);
						directionBuffer.clear();
					}


				}

				// mo¿liwoœæ manualnego wyd³u¿enia wê¿a o 1. p³ytkê, co najwy¿ej 1. na sekundê
				time3 = clock3.getElapsedTime();
				if (Keyboard::isKeyPressed(Keyboard::S) && time3.asSeconds() > 1)
				{
					snakeTile.setDirection(snakeTileVector[snakeSize - 1].getDirection());

					// count modifiers
					countModifiers(snakeTileVector[snakeSize - 1].getDirection(), sideLength, 0, modifierX, modifierY);

					snakeTile.setPosition(sf::Vector2f(snakeTileVector[snakeSize - 1].getPosition().x + modifierX, snakeTileVector[snakeSize - 1].getPosition().y + modifierY));
					snakeTileVector.push_back(snakeTile);
					++snakeSize;

					clock3.restart();
				}
			}

			else
			{
				if (Keyboard::isKeyPressed(Keyboard::Space))
				{
						gamestate = STARTED;
				}
			}
		}
		
		if (gamestate == STARTED)
		{
			// poruszanie reszt¹ wê¿a + kolizje
			time2 = clock2.getElapsedTime();
			if (time2.asSeconds() > timeAsSec)
			{
				// co siê dzieje gdy wyjedziemy poza ekran (teleportujemy na drug¹ stronê)
				for (int i = 0; i < snakeSize; ++i)
				{
					snakeTileVector[i].moveHead();
					if (snakeTileVector[i].getPosition().x < 0)
						snakeTileVector[i].setPosition(Vector2f(game.getSize().x - sideLength, snakeTileVector[i].getPosition().y));

					else if (snakeTileVector[i].getPosition().x >= game.getSize().x)
						snakeTileVector[i].setPosition(Vector2f(0, snakeTileVector[i].getPosition().y));

					else if (snakeTileVector[i].getPosition().y < 0)
						snakeTileVector[i].setPosition(Vector2f(snakeTileVector[i].getPosition().x, game.getSize().y - sideLength));

					else if (snakeTileVector[i].getPosition().y >= game.getSize().y)
						snakeTileVector[i].setPosition(Vector2f(snakeTileVector[i].getPosition().x, 0));

				}

				// wyœwietlanie pozycji g³owy co animacjê (testy)
				std::cout << "X: " << snakeTileVector[0].getPosition().x << "  Y: " << snakeTileVector[0].getPosition().y << "\n";

				// aktualizacja kierunku wszystkich p³ytek. Istotne jest to by to robiæ od najwiêkszego indexu
				// aby unikn¹æ skopiowania wartoœci z [0] do wszystkich
				for (int i = snakeSize - 1; i >= 1; --i)
				{
					snakeTileVector[i].setDirection(snakeTileVector[i - 1].getDirection());
				}

				// kolizja g³owy z reszt¹ cia³a
				// je¿eli jest kolizja: rozpocznij grê od nowa.
				for (int i = 1; i < snakeSize; ++i)
				{
					if (snakeTileVector[0].getRect().getGlobalBounds().intersects(snakeTileVector[i].getRect().getGlobalBounds()))
					{
						error("COLLISION!");

						// wyczyszczenie wektora, zresetowanie stanu gry
						snakeTileVector.clear();
						snakeTile.setDirection(Snake::Direction::UP);
						snakeTile.setPosition(sf::Vector2f(game.getSize().x / 2 - sideLength / 2, game.getSize().y / 2 - sideLength / 2));
						snakeTileVector.push_back(snakeTile);
						snakeTileVector[0].setColor(sf::Color::Yellow);

						// ustawienie drugiej p³ytki
						snakeTile.setDirection(snakeTileVector[0].getDirection());
						countModifiers(snakeTileVector[0].getDirection(), sideLength, 0, modifierX, modifierY);
						snakeTile.setPosition(sf::Vector2f(snakeTileVector[0].getPosition().x + modifierX, snakeTileVector[0].getPosition().y + modifierY));
						snakeTileVector.push_back(snakeTile);

						rect.setRandomPosition();
						snakeSize = 2;

						// wiadomoœæ koñcow¹ uzupe³niamy zanim wyzerujemy punkty
						endMessage.setString("You ate yourself! Your score: " + to_string(score) + "\nPress\"Space\" to play again!");

						score = 0;
						text.setString("Score: " + to_string(score));
						gamestate = ENDED;

					}
				}

				// kolizja g³owy z klockiem do zebrania
				if (snakeTileVector[0].getRect().getGlobalBounds().intersects(rect.getRect().getGlobalBounds()))
				{
					error("SCORE");
					++score;
					rect.setRandomPosition();

					snakeTile.setDirection(snakeTileVector[snakeSize - 1].getDirection());

					// count modifiers
					countModifiers(snakeTileVector[snakeSize - 1].getDirection(), sideLength, 0, modifierX, modifierY);

					snakeTile.setPosition(sf::Vector2f(snakeTileVector[snakeSize - 1].getPosition().x + modifierX, snakeTileVector[snakeSize - 1].getPosition().y + modifierY));
					snakeTileVector.push_back(snakeTile);
					++snakeSize;
					text.setString("Score: " + to_string(score));
				}
				clock2.restart();
			}
		}

		game.clear();

		if (gamestate == STARTED)
		{
			// drawing our snake to the screen
			for (int i = 0; i < snakeSize; ++i)
			{
				snakeTileVector[i].drawTo(game);
			}

			rect.drawTo(game);
			game.draw(text);
			game.draw(gridMessage);

			// wyœwietlanie siatki do testów
			if (grid)
			{
				printGrid(game.getSize().x, game.getSize().y, sideLength, game, 1);
			}
		}


		else
		{
			if (gamestate == START)
				game.draw(startMessage);

			else
				game.draw(endMessage);
		}

		game.display();
	}

	_getch();
	return 0;
}