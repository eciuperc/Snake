#include <string>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include <conio.h>
#include <Windows.h>
#include <time.h>

const int FIELD_SIZE = 15;
const float VIEW_HEGIHT = 662.f;
const float BORDER_SIZE = 15.f;
const float LAG = 5;
const sf::Color BACKGROUND_COLOR = sf::Color(144, 255, 251);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEGIHT * aspectRatio, VIEW_HEGIHT);
	view.setCenter((512.f + BORDER_SIZE + 1.5f * (512.f - 2 * 64.f - BORDER_SIZE)) / 2, 256);
}

void DisplayFond(sf::RenderWindow& window, int score, int difficulty)
{
	window.clear(BACKGROUND_COLOR);

	//Border of the field

	sf::RectangleShape border1;
	border1.setFillColor(sf::Color::Black);
	border1.setSize(sf::Vector2f(BORDER_SIZE, 512.f + 2 * BORDER_SIZE));
	border1.setPosition(-BORDER_SIZE, -BORDER_SIZE);

	window.draw(border1);

	sf::RectangleShape border2;
	border2.setFillColor(sf::Color::Black);
	border2.setSize(sf::Vector2f(BORDER_SIZE, 512.f + 2 * BORDER_SIZE));
	border2.setPosition(512.f, -BORDER_SIZE);

	window.draw(border2);

	sf::RectangleShape border3;
	border3.setFillColor(sf::Color::Black);
	border3.setSize(sf::Vector2f(512.f, BORDER_SIZE));
	border3.setPosition(0.f, -BORDER_SIZE);

	window.draw(border3);

	sf::RectangleShape border4;
	border4.setFillColor(sf::Color::Black);
	border4.setSize(sf::Vector2f(512.f, BORDER_SIZE));
	border4.setPosition(0.f, 512.f);

	window.draw(border4);

	int height = 512.f - 64.f * 2;

	sf::RectangleShape edgefullblack;
	edgefullblack.setFillColor(sf::Color::Black);
	edgefullblack.setSize(sf::Vector2f(1.5f * (height - BORDER_SIZE), height));
	edgefullblack.setPosition(512.f + BORDER_SIZE, 64.f);

	window.draw(edgefullblack);

	sf::RectangleShape edgefullwhite1;
	edgefullwhite1.setFillColor(BACKGROUND_COLOR);
	edgefullwhite1.setSize(sf::Vector2f(1.5f * (height - BORDER_SIZE) - BORDER_SIZE, (height - 3 * BORDER_SIZE) * 2.f / 5));
	edgefullwhite1.setPosition(512.f + BORDER_SIZE, 64.f + BORDER_SIZE);

	window.draw(edgefullwhite1);

	sf::RectangleShape edgefullwhite2;
	edgefullwhite2.setFillColor(BACKGROUND_COLOR);
	edgefullwhite2.setSize(sf::Vector2f(1.5f * (height - BORDER_SIZE) - BORDER_SIZE, (height - 3 * BORDER_SIZE) * 3.f / 5));
	edgefullwhite2.setPosition(512.f + BORDER_SIZE, 64.f + 2 * BORDER_SIZE + (height - 3 * BORDER_SIZE) * 2.f / 5);

	window.draw(edgefullwhite2);



	//Display score

	sf::Text writescore;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	writescore.setString("Score :");
	writescore.setFont(font);

	writescore.setCharacterSize(0.85f * edgefullwhite1.getSize().y / 2.0f);

	sf::FloatRect writescoreRect = writescore.getLocalBounds();
	writescore.setOrigin(writescoreRect.left + writescoreRect.width / 2.0f,
		writescoreRect.top + writescoreRect.height / 2.0f);
	writescore.setPosition(edgefullwhite1.getPosition() + sf::Vector2f(edgefullwhite1.getSize().x / 2.f, edgefullwhite1.getSize().y / 4.f));

	writescore.setFillColor(sf::Color::Black);

	window.draw(writescore);

	sf::Text textscore;

	std::string scorestring = std::to_string(score);
	textscore.setString(scorestring);
	textscore.setFont(font);

	textscore.setCharacterSize(0.9f * edgefullwhite1.getSize().y / 2.0f);

	sf::FloatRect textscoreRect = textscore.getLocalBounds();
	textscore.setOrigin(textscoreRect.left + textscoreRect.width / 2.0f,
		textscoreRect.top + textscoreRect.height / 2.0f);
	textscore.setPosition(edgefullwhite1.getPosition() + sf::Vector2f(edgefullwhite1.getSize().x / 2.f, edgefullwhite1.getSize().y * 3.f / 4.f));

	textscore.setFillColor(sf::Color::Black);

	window.draw(textscore);



	//Display keys

	sf::Text pressp;

	pressp.setString("Press 'p' to pause");
	pressp.setFont(font);

	pressp.setCharacterSize(0.65f * edgefullwhite2.getSize().y / 3.0f);

	sf::FloatRect presspRect = pressp.getLocalBounds();
	pressp.setOrigin(presspRect.left + presspRect.width / 2.0f,
		presspRect.top + presspRect.height / 2.0f);
	pressp.setPosition(edgefullwhite2.getPosition() + sf::Vector2f(edgefullwhite2.getSize().x / 2.f, edgefullwhite2.getSize().y * 1.f / 6.f));

	pressp.setFillColor(sf::Color::Black);

	window.draw(pressp);


	sf::Text pressx;

	pressx.setString("Press 'x' to exit");
	pressx.setFont(font);

	pressx.setCharacterSize(0.65f * edgefullwhite2.getSize().y / 3.0f);

	sf::FloatRect pressxRect = pressx.getLocalBounds();
	pressx.setOrigin(pressxRect.left + pressxRect.width / 2.0f,
		pressxRect.top + pressxRect.height / 2.0f);
	pressx.setPosition(edgefullwhite2.getPosition() + sf::Vector2f(edgefullwhite2.getSize().x / 2.f, edgefullwhite2.getSize().y * 3.f / 6.f));

	pressx.setFillColor(sf::Color::Black);

	window.draw(pressx);


	sf::Text difftext;

	difftext.setString("Difficulty : ");
	difftext.setFont(font);

	difftext.setCharacterSize(0.65f * edgefullwhite2.getSize().y / 3.0f);

	sf::FloatRect difftextRect = difftext.getLocalBounds();
	difftext.setOrigin(difftextRect.left + difftextRect.width / 2.0f,
		difftextRect.top + difftextRect.height / 2.0f);

	difftext.setFillColor(sf::Color::Black);



	sf::Text diff;

	// Define difficulty text
	switch (difficulty)
	{
	case(1):
	{
		diff.setString("Very easy");
		diff.setFillColor(sf::Color(64, 255, 64));
		break;
	}
	case(2):
	{
		diff.setString("Easy");
		diff.setFillColor(sf::Color(0, 255, 0));
		break;
	}
	case(3):
	{
		diff.setString("Normal");
		diff.setFillColor(sf::Color(255, 255, 0));
		break;
	}
	case(4):
	{
		diff.setString("Hard");
		diff.setFillColor(sf::Color(255, 128, 0));
		break;
	}
	case(5):
	{
		diff.setString("Very hard");
		diff.setFillColor(sf::Color(255, 0, 0));
		break;
	}
	case(6):
	{
		diff.setString("Impossible");
		diff.setFillColor(sf::Color(96, 0, 0));
		break;
	}
	}

	diff.setFont(font);

	diff.setCharacterSize(0.65f * edgefullwhite2.getSize().y / 3.0f);

	sf::FloatRect diffRect = diff.getLocalBounds();
	diff.setOrigin(diffRect.left + diffRect.width / 2.0f,
		diffRect.top + diffRect.height / 2.0f);

	difftext.setPosition(edgefullwhite2.getPosition() + sf::Vector2f(edgefullwhite2.getSize().x / 2.f - diffRect.width / 2.0f, edgefullwhite2.getSize().y * 5.f / 6.f));
	diff.setPosition(edgefullwhite2.getPosition() + sf::Vector2f(edgefullwhite2.getSize().x / 2.f + difftextRect.width / 2.0f, edgefullwhite2.getSize().y * 5.f / 6.f));

	window.draw(difftext);
	window.draw(diff);
}

void DisplayWin(sf::RenderWindow& window, sf::View& view, int score, sf::FloatRect& winRect1, sf::FloatRect& winRect2)
{
	window.clear(BACKGROUND_COLOR);

	sf::Text wintxt1;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	wintxt1.setString("You won!");
	wintxt1.setFont(font);

	wintxt1.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect wintxt1Rect = wintxt1.getLocalBounds();
	wintxt1.setOrigin(wintxt1Rect.left + wintxt1Rect.width / 2.0f, wintxt1Rect.top + wintxt1Rect.height / 2.0f);
	wintxt1.setPosition(view.getCenter().x, view.getCenter().y - 225);

	wintxt1.setFillColor(sf::Color::Black);

	window.draw(wintxt1);



	sf::Text winscore;

	winscore.setString("Score : " + std::to_string(score));
	winscore.setFont(font);

	winscore.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect winscoreRect = winscore.getLocalBounds();
	winscore.setOrigin(winscoreRect.left + winscoreRect.width / 2.0f, winscoreRect.top + winscoreRect.height / 2.0f);
	winscore.setPosition(view.getCenter().x, view.getCenter().y - 75);

	winscore.setFillColor(sf::Color::Black);

	window.draw(winscore);



	sf::Text wintxt2;

	wintxt2.setString("Play again?");
	wintxt2.setFont(font);

	wintxt2.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect wintxt2Rect = wintxt2.getLocalBounds();
	wintxt2.setOrigin(wintxt2Rect.left + wintxt2Rect.width / 2.0f, wintxt2Rect.top + wintxt2Rect.height / 2.0f);
	wintxt2.setPosition(view.getCenter().x, view.getCenter().y + 75);

	wintxt2.setFillColor(sf::Color::Black);

	window.draw(wintxt2);

	sf::Text wintxt3;

	wintxt3.setString("Yes");
	wintxt3.setFont(font);

	wintxt3.setCharacterSize(view.getSize().y / 10);

	winRect1 = wintxt3.getLocalBounds();
	wintxt3.setOrigin(winRect1.left + winRect1.width / 2.0f, winRect1.top + winRect1.height / 2.0f);
	wintxt3.setPosition(view.getCenter().x - 150, view.getCenter().y + 225);

	wintxt3.setFillColor(sf::Color::Black);

	window.draw(wintxt3);



	sf::Text wintxt4;

	wintxt4.setString("No");
	wintxt4.setFont(font);

	wintxt4.setCharacterSize(view.getSize().y / 10);

	winRect2 = wintxt4.getLocalBounds();
	wintxt4.setOrigin(winRect2.left + winRect2.width / 2.0f, winRect2.top + winRect2.height / 2.0f);
	wintxt4.setPosition(view.getCenter().x + 150, view.getCenter().y + 225);

	wintxt4.setFillColor(sf::Color::Black);

	window.draw(wintxt4);

	window.display();
}

void DisplayCrashed(sf::RenderWindow& window, sf::View& view, int score, sf::FloatRect& failtxt3Rect, sf::FloatRect& failtxt4Rect)
{
	window.clear(BACKGROUND_COLOR);

	sf::Text failtxt1;
	sf::Font font;
	font.loadFromFile("arial.ttf");

	failtxt1.setString("Game Over");
	failtxt1.setFont(font);

	failtxt1.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect failtxt1Rect = failtxt1.getLocalBounds();
	failtxt1.setOrigin(failtxt1Rect.left + failtxt1Rect.width / 2.0f, failtxt1Rect.top + failtxt1Rect.height / 2.0f);
	failtxt1.setPosition(view.getCenter().x, view.getCenter().y - 225);

	failtxt1.setFillColor(sf::Color::Black);

	window.draw(failtxt1);



	sf::Text failscore;

	failscore.setString("Score : " + std::to_string(score));
	failscore.setFont(font);

	failscore.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect failscoreRect = failscore.getLocalBounds();
	failscore.setOrigin(failscoreRect.left + failscoreRect.width / 2.0f, failscoreRect.top + failscoreRect.height / 2.0f);
	failscore.setPosition(view.getCenter().x, view.getCenter().y - 75);

	failscore.setFillColor(sf::Color::Black);

	window.draw(failscore);



	sf::Text failtxt2;

	failtxt2.setString("Play again?");
	failtxt2.setFont(font);

	failtxt2.setCharacterSize(view.getSize().y / 10);

	sf::FloatRect failtxt2Rect = failtxt2.getLocalBounds();
	failtxt2.setOrigin(failtxt2Rect.left + failtxt2Rect.width / 2.0f, failtxt2Rect.top + failtxt2Rect.height / 2.0f);
	failtxt2.setPosition(view.getCenter().x, view.getCenter().y + 75);

	failtxt2.setFillColor(sf::Color::Black);

	window.draw(failtxt2);

	sf::Text failtxt3;

	failtxt3.setString("Yes");
	failtxt3.setFont(font);

	failtxt3.setCharacterSize(view.getSize().y / 10);

	failtxt3Rect = failtxt3.getLocalBounds();
	failtxt3.setOrigin(failtxt3Rect.left + failtxt3Rect.width / 2.0f, failtxt3Rect.top + failtxt3Rect.height / 2.0f);
	failtxt3.setPosition(view.getCenter().x - 150, view.getCenter().y + 225);

	failtxt3.setFillColor(sf::Color::Black);

	window.draw(failtxt3);



	sf::Text failtxt4;

	failtxt4.setString("No");
	failtxt4.setFont(font);

	failtxt4.setCharacterSize(view.getSize().y / 10);

	failtxt4Rect = failtxt4.getLocalBounds();
	failtxt4.setOrigin(failtxt4Rect.left + failtxt4Rect.width / 2.0f, failtxt4Rect.top + failtxt4Rect.height / 2.0f);
	failtxt4.setPosition(view.getCenter().x + 150, view.getCenter().y + 225);

	failtxt4.setFillColor(sf::Color::Black);

	window.draw(failtxt4);

	window.display();
}

void DisplayMainMenu(sf::RenderWindow& window, sf::View& view, sf::FloatRect& diff1Rect, sf::FloatRect& diff2Rect, sf::FloatRect& diff3Rect, sf::FloatRect& diff4Rect, sf::FloatRect& diff5Rect, sf::FloatRect& diff6Rect)
{
	window.clear(BACKGROUND_COLOR);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text seldif;

	seldif.setString("Select difficulty : ");
	seldif.setFont(font);

	seldif.setCharacterSize(0.9f * view.getSize().y / 10);

	sf::FloatRect seldifRect = seldif.getLocalBounds();
	seldif.setOrigin(seldifRect.left + seldifRect.width / 2.0f, seldifRect.top + seldifRect.height / 2.0f);
	seldif.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.15f);

	seldif.setFillColor(sf::Color::Black);

	window.draw(seldif);







	sf::Text txt1;

	txt1.setString("1 : ");
	txt1.setFont(font);

	txt1.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt1Rect = txt1.getLocalBounds();
	txt1.setOrigin(txt1Rect.left + txt1Rect.width / 2.0f, txt1Rect.top + txt1Rect.height / 2.0f);
	txt1.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.35f);

	txt1.setFillColor(sf::Color(64, 255, 64));

	window.draw(txt1);



	sf::Text txt2;

	txt2.setString("2 : ");
	txt2.setFont(font);

	txt2.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt2Rect = txt2.getLocalBounds();
	txt2.setOrigin(txt2Rect.left + txt2Rect.width / 2.0f, txt2Rect.top + txt2Rect.height / 2.0f);
	txt2.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.45f);

	txt2.setFillColor(sf::Color(0, 255, 0));

	window.draw(txt2);



	sf::Text txt3;

	txt3.setString("3 : ");
	txt3.setFont(font);

	txt3.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt3Rect = txt3.getLocalBounds();
	txt3.setOrigin(txt3Rect.left + txt3Rect.width / 2.0f, txt3Rect.top + txt3Rect.height / 2.0f);
	txt3.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.55f);

	txt3.setFillColor(sf::Color(255, 255, 0));

	window.draw(txt3);



	sf::Text txt4;

	txt4.setString("4 : ");
	txt4.setFont(font);

	txt4.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt4Rect = txt4.getLocalBounds();
	txt4.setOrigin(txt4Rect.left + txt4Rect.width / 2.0f, txt4Rect.top + txt4Rect.height / 2.0f);
	txt4.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.65f);

	txt4.setFillColor(sf::Color(255, 128, 0));

	window.draw(txt4);



	sf::Text txt5;

	txt5.setString("5 : ");
	txt5.setFont(font);

	txt5.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt5Rect = txt5.getLocalBounds();
	txt5.setOrigin(txt5Rect.left + txt5Rect.width / 2.0f, txt5Rect.top + txt5Rect.height / 2.0f);
	txt5.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.75f);

	txt5.setFillColor(sf::Color(255, 0, 0));

	window.draw(txt5);



	sf::Text txt6;

	txt6.setString("6 : ");
	txt6.setFont(font);

	txt6.setCharacterSize(0.7f * view.getSize().y / 10);

	sf::FloatRect txt6Rect = txt6.getLocalBounds();
	txt6.setOrigin(txt6Rect.left + txt6Rect.width / 2.0f, txt6Rect.top + txt6Rect.height / 2.0f);
	txt6.setPosition(view.getCenter().x - view.getSize().x / 2.f + 200, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.85f);

	txt6.setFillColor(sf::Color(96, 0, 0));

	window.draw(txt6);







	sf::Text diff1;

	diff1.setString("Very easy");
	diff1.setFont(font);

	diff1.setCharacterSize(0.7f * view.getSize().y / 10);

	diff1Rect = diff1.getLocalBounds();
	diff1.setOrigin(diff1Rect.left + diff1Rect.width / 2.f, diff1Rect.top + diff1Rect.height / 2.0f);
	diff1.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.35f);

	diff1.setFillColor(sf::Color(64, 255, 64));

	window.draw(diff1);



	sf::Text diff2;

	diff2.setString("Easy");
	diff2.setFont(font);

	diff2.setCharacterSize(0.7f * view.getSize().y / 10);

	diff2Rect = diff2.getLocalBounds();
	diff2.setOrigin(diff2Rect.left + diff2Rect.width / 2.f, diff2Rect.top + diff2Rect.height / 2.0f);
	diff2.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.45f);

	diff2.setFillColor(sf::Color(0, 255, 0));

	window.draw(diff2);



	sf::Text diff3;

	diff3.setString("Normal");
	diff3.setFont(font);

	diff3.setCharacterSize(0.7f * view.getSize().y / 10);

	diff3Rect = diff3.getLocalBounds();
	diff3.setOrigin(diff3Rect.left + diff3Rect.width / 2.f, diff3Rect.top + diff3Rect.height / 2.0f);
	diff3.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.55f);

	diff3.setFillColor(sf::Color(255, 255, 0));

	window.draw(diff3);



	sf::Text diff4;

	diff4.setString("Hard");
	diff4.setFont(font);

	diff4.setCharacterSize(0.7f * view.getSize().y / 10);

	diff4Rect = diff4.getLocalBounds();
	diff4.setOrigin(diff4Rect.left + diff4Rect.width / 2.f, diff4Rect.top + diff4Rect.height / 2.0f);
	diff4.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.65f);

	diff4.setFillColor(sf::Color(255, 128, 0));

	window.draw(diff4);



	sf::Text diff5;

	diff5.setString("Very hard");
	diff5.setFont(font);

	diff5.setCharacterSize(0.7f * view.getSize().y / 10);

	diff5Rect = diff5.getLocalBounds();
	diff5.setOrigin(diff5Rect.left + diff5Rect.width / 2.f, diff5Rect.top + diff5Rect.height / 2.0f);
	diff5.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.75f);

	diff5.setFillColor(sf::Color(255, 0, 0));

	window.draw(diff5);



	sf::Text diff6;

	diff6.setString("Impossible");
	diff6.setFont(font);

	diff6.setCharacterSize(0.7f * view.getSize().y / 10);

	diff6Rect = diff6.getLocalBounds();
	diff6.setOrigin(diff6Rect.left + diff6Rect.width / 2.f, diff6Rect.top + diff6Rect.height / 2.0f);
	diff6.setPosition(view.getCenter().x, view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.85f);

	diff6.setFillColor(sf::Color(96, 0, 0));

	window.draw(diff6);



	window.display();
}

int main()
{
beginning:
	float timedelay = 1.f;
	int difficulty = 0;

	sf::RenderWindow window(sf::VideoMode(500, 500), "Snake with SFML", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	::ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
	window.setKeyRepeatEnabled(false);
	sf::View view(sf::Vector2f(VIEW_HEGIHT / 2, 500.f), sf::Vector2f(VIEW_HEGIHT, 1000.f));
	sf::View viewtest(sf::Vector2f(-30.f, -30.f), sf::Vector2f(100.f, 100.f));

	sf::Texture bodyTexture;
	bodyTexture.loadFromFile("Gray_Circle.png");
	sf::Texture headTexture;
	headTexture.loadFromFile("Gray_Circle_with_eyes.png");
	sf::Image icon;
	icon.loadFromFile("Gray_Circle_with_eyes.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	int tailleserpent = 5;
	Snake snake(&bodyTexture, &headTexture, sf::Vector2u(FIELD_SIZE / 2, FIELD_SIZE / 2), tailleserpent, FIELD_SIZE);

	//Defining the apple

	srand(time(NULL));
	sf::Vector2i apple;
	apple.x = rand() % FIELD_SIZE;
	apple.y = rand() % FIELD_SIZE;
	sf::RectangleShape applesprite;
	applesprite.setSize(sf::Vector2f(512.f / FIELD_SIZE, 512.f / FIELD_SIZE));
	applesprite.setPosition(apple.y * 512.f / FIELD_SIZE, apple.x * 512.f / FIELD_SIZE);
	sf::Texture appleTexture;
	appleTexture.loadFromFile("Apple_Sprite.png");
	applesprite.setTexture(&appleTexture);

	std::list<char> listinput = { 'z' };
	float timeframe = 0.f;
	bool nextframe = true;
	bool pause = false;
	bool preleased = true;
	sf::Clock clock;

	sf::Event evnt;

	while (window.pollEvent(evnt))
	{
		switch (evnt.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::Resized:
			ResizeView(window, view);
			break;
		}
	}
	window.setView(view);

	// Setting game menu

	sf::FloatRect diff1Rect;
	sf::FloatRect diff2Rect;
	sf::FloatRect diff3Rect;
	sf::FloatRect diff4Rect;
	sf::FloatRect diff5Rect;
	sf::FloatRect diff6Rect;
	DisplayMainMenu(window, view, diff1Rect, diff2Rect, diff3Rect, diff4Rect, diff5Rect, diff6Rect);

	float lowerboundx1 = view.getCenter().x - (diff1Rect.left + diff1Rect.width / 2.f);
	float lowerboundy1 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.35f - (diff1Rect.top + diff1Rect.height / 2.0f);
	float upperboundx1 = view.getCenter().x + (diff1Rect.left + diff1Rect.width / 2.f);
	float upperboundy1 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.35f + (diff1Rect.top + diff1Rect.height / 2.0f);

	float lowerboundx2 = view.getCenter().x - (diff2Rect.left + diff2Rect.width / 2.f);
	float lowerboundy2 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.45f - (diff2Rect.top + diff2Rect.height / 2.0f);
	float upperboundx2 = view.getCenter().x + (diff2Rect.left + diff2Rect.width / 2.f);
	float upperboundy2 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.45f + (diff2Rect.top + diff2Rect.height / 2.0f);

	float lowerboundx3 = view.getCenter().x - (diff3Rect.left + diff3Rect.width / 2.f);
	float lowerboundy3 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.55f - (diff3Rect.top + diff3Rect.height / 2.0f);
	float upperboundx3 = view.getCenter().x + (diff3Rect.left + diff3Rect.width / 2.f);
	float upperboundy3 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.55f + (diff3Rect.top + diff3Rect.height / 2.0f);

	float lowerboundx4 = view.getCenter().x - (diff4Rect.left + diff4Rect.width / 2.f);
	float lowerboundy4 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.65f - (diff4Rect.top + diff4Rect.height / 2.0f);
	float upperboundx4 = view.getCenter().x + (diff4Rect.left + diff4Rect.width / 2.f);
	float upperboundy4 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.65f + (diff4Rect.top + diff4Rect.height / 2.0f);

	float lowerboundx5 = view.getCenter().x - (diff5Rect.left + diff5Rect.width / 2.f);
	float lowerboundy5 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.75f - (diff5Rect.top + diff5Rect.height / 2.0f);
	float upperboundx5 = view.getCenter().x + (diff5Rect.left + diff5Rect.width / 2.f);
	float upperboundy5 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.75f + (diff5Rect.top + diff5Rect.height / 2.0f);

	float lowerboundx6 = view.getCenter().x - (diff6Rect.left + diff6Rect.width / 2.f);
	float lowerboundy6 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.85f - (diff6Rect.top + diff6Rect.height / 2.0f);
	float upperboundx6 = view.getCenter().x + (diff2Rect.left + diff2Rect.width / 2.f);
	float upperboundy6 = view.getCenter().y - view.getSize().y * 1.f / 2.f + view.getSize().y * 0.85f + (diff6Rect.top + diff6Rect.height / 2.0f);

	// Setting game difficulty

	while (window.isOpen())
	{
		Sleep(LAG);

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				window.display();
				window.display();
				break;
			}

			// get the current mouse position in the window
			sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

			// convert it to world coordinates
			sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) || (worldPos.x >= lowerboundx1 && worldPos.x <= upperboundx1 && worldPos.y >= lowerboundy1 && worldPos.y <= upperboundy1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 0.7f;
				difficulty = 1;
				goto begingame;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) || (worldPos.x >= lowerboundx2 && worldPos.x <= upperboundx2 && worldPos.y >= lowerboundy2 && worldPos.y <= upperboundy2 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 0.4f;
				difficulty = 2;
				goto begingame;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) || (worldPos.x >= lowerboundx3 && worldPos.x <= upperboundx3 && worldPos.y >= lowerboundy3 && worldPos.y <= upperboundy3 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 0.2f;
				difficulty = 3;
				goto begingame;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) || (worldPos.x >= lowerboundx4 && worldPos.x <= upperboundx4 && worldPos.y >= lowerboundy4 && worldPos.y <= upperboundy4 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 0.1f;
				difficulty = 4;
				goto begingame;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) || (worldPos.x >= lowerboundx5 && worldPos.x <= upperboundx5 && worldPos.y >= lowerboundy5 && worldPos.y <= upperboundy5 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 0.05f;
				difficulty = 5;
				goto begingame;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) || (worldPos.x >= lowerboundx6 && worldPos.x <= upperboundx6 && worldPos.y >= lowerboundy6 && worldPos.y <= upperboundy6 && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
			{
				timedelay = 1.f / 64;
				difficulty = 6;
				goto begingame;
			}
		}
	}

begingame:

	clock.restart();
	DisplayFond(window, snake.score, difficulty);
	snake.DrawSnake(window);
	window.draw(applesprite);
	window.display();

	while (window.isOpen())
	{
		Sleep(LAG);

		sf::Event evnt;

		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::Resized:
			{
				ResizeView(window, view);
				window.display();
				window.display();
				break;
			}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !pause)
		{
			if (listinput.back() != 'z')
			{
				listinput.push_back('z');
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !pause)
		{
			if (listinput.back() != 's')
			{
				listinput.push_back('s');
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !pause)
		{
			if (listinput.back() != 'd')
			{
				listinput.push_back('d');
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !pause)
		{
			if (listinput.back() != 'q')
			{
				listinput.push_back('q');
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && preleased)
		{
			preleased = false;
			if (!pause)
			{
				pause = true;
			}
			else
			{
				pause = false;
				clock.restart();
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			preleased = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
			window.close();

		timeframe += clock.restart().asSeconds();
		if (timeframe >= timedelay)
		{
			timeframe -= timedelay;
			nextframe = true;
		}
		else
		{
			nextframe = false;
		}

		if (nextframe && !pause)
		{

			nextframe = false;

			// Si on gagne (ie. plus de place sur la map)

			if (snake.score == FIELD_SIZE * FIELD_SIZE - tailleserpent) {

				sf::FloatRect winRect1;
				sf::FloatRect winRect2;

				DisplayWin(window, view, snake.score, winRect1, winRect2);

				float yeslowerboundx = view.getCenter().x - 150 - winRect1.left - winRect1.width / 2.0f;
				float yeslowerboundy = view.getCenter().y + 225 - winRect1.top - winRect1.height / 2.0f;
				float yesupperboundx = view.getCenter().x - 150 + winRect1.left + winRect1.width / 2.0f;
				float yesupperboundy = view.getCenter().y + 225 + winRect1.top + winRect1.height / 2.0f;

				float nolowerboundx = view.getCenter().x + 150 - winRect2.left - winRect2.width / 2.0f;
				float nolowerboundy = view.getCenter().y + 225 - winRect2.top - winRect2.height / 2.0f;
				float noupperboundx = view.getCenter().x + 150 + winRect2.left + winRect2.width / 2.0f;
				float noupperboundy = view.getCenter().y + 225 + winRect2.top + winRect2.height / 2.0f;

				while (window.isOpen())
				{
					Sleep(LAG);

					sf::Event evnt;

					while (window.pollEvent(evnt))
					{
						switch (evnt.type)
						{
						case sf::Event::Closed:
							window.close();
							break;
						case sf::Event::Resized:
							ResizeView(window, view);
							window.display();
							window.display();
							break;
						}

						// get the current mouse position in the window
						sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

						// convert it to world coordinates
						sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || (worldPos.x >= yeslowerboundx && worldPos.x <= yesupperboundx && worldPos.y >= yeslowerboundy && worldPos.y <= yesupperboundy && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
							goto beginning;
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || (worldPos.x >= nolowerboundx && worldPos.x <= noupperboundx && worldPos.y >= nolowerboundy && worldPos.y <= noupperboundy && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
							goto end;

					}
				}
			}

			if (listinput.size() > 1)
			{
				listinput.pop_front();
			}
			snake.Update(listinput.front(), apple);

			// Si on perd

			if (snake.crashed)
			{
				sf::FloatRect failtxt3Rect;
				sf::FloatRect failtxt4Rect;

				DisplayCrashed(window, view, snake.score, failtxt3Rect, failtxt4Rect);

				float yeslowerboundx = view.getCenter().x - 150 - failtxt3Rect.left - failtxt3Rect.width / 2.0f;
				float yeslowerboundy = view.getCenter().y + 225 - failtxt3Rect.top - failtxt3Rect.height / 2.0f;
				float yesupperboundx = view.getCenter().x - 150 + failtxt3Rect.left + failtxt3Rect.width / 2.0f;
				float yesupperboundy = view.getCenter().y + 225 + failtxt3Rect.top + failtxt3Rect.height / 2.0f;

				float nolowerboundx = view.getCenter().x + 150 - failtxt4Rect.left - failtxt4Rect.width / 2.0f;
				float nolowerboundy = view.getCenter().y + 225 - failtxt4Rect.top - failtxt4Rect.height / 2.0f;
				float noupperboundx = view.getCenter().x + 150 + failtxt4Rect.left + failtxt4Rect.width / 2.0f;
				float noupperboundy = view.getCenter().y + 225 + failtxt4Rect.top + failtxt4Rect.height / 2.0f;

				while (window.isOpen())
				{
					Sleep(LAG);

					sf::Event evnt;

					while (window.pollEvent(evnt))
					{
						switch (evnt.type)
						{
						case sf::Event::Closed:
							window.close();
							break;
						case sf::Event::Resized:
							ResizeView(window, view);
							window.display();
							window.display();
							break;
						}

						// get the current mouse position in the window
						sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

						// convert it to world coordinates
						sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

						if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) || (worldPos.x >= yeslowerboundx && worldPos.x <= yesupperboundx && worldPos.y >= yeslowerboundy && worldPos.y <= yesupperboundy && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
							goto beginning;
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) || (worldPos.x >= nolowerboundx && worldPos.x <= noupperboundx && worldPos.y >= nolowerboundy && worldPos.y <= noupperboundy && sf::Mouse::isButtonPressed(sf::Mouse::Left)))
							goto end;

					}
				}
			}

			// Autres cas

			else {

				// Replace apple

				while (!snake.IsAvaliable(apple.x, apple.y) && snake.score < FIELD_SIZE * FIELD_SIZE - tailleserpent)
				{
					apple.x = rand() % FIELD_SIZE;
					apple.y = rand() % FIELD_SIZE;
					if (snake.IsAvaliable(apple.x, apple.y))
					{
						applesprite.setPosition(apple.y * 512.f / FIELD_SIZE, apple.x * 512.f / FIELD_SIZE);
					}
				}

				window.setView(view);
				DisplayFond(window, snake.score, difficulty);
				snake.DrawSnake(window);
				window.draw(applesprite);
				//window.draw(testbody);
				//window.draw(testhead);
				window.display();
			}
		}
	}

end:

	snake.CleanSnake();

	return 0;
}