#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

class Snake
{
public:
	Snake(sf::Texture* bodyTexture, sf::Texture* headTexture, sf::Vector2u InitialPosition, int InitialLength, int FIELD_SIZE);

	void Update(char input, sf::Vector2i apple);
	bool IsAvaliable(int applex, int appley);
	void DrawSnake(sf::RenderWindow& window);
	void CleanSnake();

	bool crashed = false;
	int score;

private:
	sf::Texture* bodyTexture;
	sf::Texture* headTexture;
	sf::Vector2i headPosition;
	int headdirection;     // Haut = 1, Droite = 2, Bas = 3, Gauche = 4
	int GrowLeft;
	int** snakemat;
	std::list<sf::Vector2u> snakelist;

	int FIELD_SIZE;
};

