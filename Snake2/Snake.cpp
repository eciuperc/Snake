#include "Snake.h"

Snake::Snake(sf::Texture* bodyTexture, sf::Texture* headTexture, sf::Vector2u InitialPosition, int InitialLength, int FIELD_SIZE)
{
	this->bodyTexture = bodyTexture;
	this->headTexture = headTexture;
	this->FIELD_SIZE = FIELD_SIZE;

	unsigned int initialx = InitialPosition.x;
	unsigned int initialy = InitialPosition.y;
	headPosition.x = initialx;
	headPosition.y = initialy;
	headdirection = 1;
	GrowLeft = InitialLength - 1;
	score = 0;

	snakemat = new int* [FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		snakemat[i] = new int[FIELD_SIZE];
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			snakemat[i][j] = 0;
		}
	}
	snakemat[initialx][initialy] = 1;

	snakelist.push_back(InitialPosition);
}


void Snake::Update(char input, sf::Vector2i apple)
{
	if (input == 'z')
	{
		headdirection = 1;
	}
	if (input == 'd')
	{
		headdirection = 2;
	}
	if (input == 's')
	{
		headdirection = 3;
	}
	if (input == 'q')
	{
		headdirection = 4;
	}

	switch (headdirection)
	{
	case(1): headPosition.x--; break;
	case(2): headPosition.y++; break;
	case(3): headPosition.x++; break;
	case(4): headPosition.y--; break;
	}

	//Check if there is a collision

	if (headPosition.x < 0 || headPosition.x >= FIELD_SIZE || headPosition.y < 0 || headPosition.y >= FIELD_SIZE || snakemat[headPosition.x][headPosition.y])
	{
		crashed = true;
	}

	if (!crashed)
	{
		snakemat[headPosition.x][headPosition.y] = 1;
		snakelist.push_back(sf::Vector2u(headPosition.x, headPosition.y));

		bool eatenapple = false;

		//Detecting if it has eaten the apple

		if (headPosition == apple)
		{
			++score;
			eatenapple = true;
		}

		if (!eatenapple && GrowLeft == 0)
		{
			sf::Vector2u tail = snakelist.front();
			snakelist.pop_front();
			snakemat[tail.x][tail.y] = 0;
		}

		if (!eatenapple)
			GrowLeft = std::max(GrowLeft - 1, 0);
	}
}


bool Snake::IsAvaliable(int applex, int appley)
{
	return !snakemat[applex][appley];
}


void Snake::DrawSnake(sf::RenderWindow& window)
{
	//system("cls");
	//for (int i = 0; i < FIELD_SIZE; ++i)
	//{
	//	for (int j = 0; j < FIELD_SIZE; ++j)
	//	{
	//		std::cout << snakemat[i][j] << ' ';
	//	}
	//	std::cout << std::endl;
	//}

	sf::RectangleShape head;
	head.setSize(sf::Vector2f(512.f / FIELD_SIZE, 512.f / FIELD_SIZE));
	head.setTexture(headTexture);

	switch (headdirection)
	{
	case(1):
	{
		head.setPosition(headPosition.y * 512.f / FIELD_SIZE, headPosition.x * 512.f / FIELD_SIZE);
		break;
	}
	case(2):
	{
		head.setPosition((headPosition.y + 1) * 512.f / FIELD_SIZE, headPosition.x * 512.f / FIELD_SIZE);
		head.rotate(90.f);
		break;
	}
	case(3):
	{
		head.setPosition((headPosition.y + 1) * 512.f / FIELD_SIZE, (headPosition.x + 1) * 512.f / FIELD_SIZE);
		head.rotate(180.f);
		break;
	}
	case(4):
	{
		head.setPosition(headPosition.y * 512.f / FIELD_SIZE, (headPosition.x + 1) * 512.f / FIELD_SIZE);
		head.rotate(270.f);
		break;
	}
	}

	window.draw(head);

	for (sf::Vector2u part : snakelist)
	{
		if (part.x != headPosition.x || part.y != headPosition.y)
		{
			sf::RectangleShape bodypart;
			bodypart.setSize(sf::Vector2f(512.f / FIELD_SIZE, 512.f / FIELD_SIZE));
			bodypart.setPosition(part.y * 512.f / FIELD_SIZE, part.x * 512.f / FIELD_SIZE);
			bodypart.setTexture(bodyTexture);

			window.draw(bodypart);
		}
	}
}



void Snake::CleanSnake()
{
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		delete[]snakemat[i];
	}
	delete[]snakemat;
}