#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Block.h"
#include "GradeGenerator.h"

using namespace sf;
using namespace std;

SoundBuffer bWinner, bSelect;
Sound win, selectSound;

Font font;

void loadResources();


// Author Walter HartWell
// This program is garbage
// lots of code duplicate
// Code Bloat
// Redundant Code

int main()
{
	Texture t1,t2;
	if (!t1.loadFromFile("Assets/notpass.jpg")) EXIT_FAILURE;
	if (!t2.loadFromFile("Assets/trapcard.jpg")) EXIT_FAILURE;
	Sprite trapCard(t2);
	Sprite notPass(t1);
	trapCard.setScale(.4, .3);
	trapCard.setPosition(1000,320);
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(640, 704), "Grade Generator for Wizard Professor");
	window.setFramerateLimit(60);

	loadResources();

	Block blocks[10][10];

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			int num = rand() % (100 - 50) + 50;
			blocks[i][j] = Block(Color::White, Color::Black, Vector2f(64, 64));
			blocks[i][j].textSettings(to_string(num), font, .6, Color::Black);
			blocks[i][j].setTextPosition(j * 64, (1 + i) * 64);
			blocks[i][j].getText()->setScale(.4, .5);
			blocks[i][j].setPosition(j * 64, (1 + i) * 64);
		}
	}

	Block button(Color::White, Color::Black, Vector2f(315, 55));
	button.textSettings("GENERATE GRADES", font, .6, Color::Black);
	button.setTextPosition(-130, -10);
	button.getText()->setPosition(20, 25);
	button.setPosition(5, 5);
	notPass.setScale(1.1, .29);
	notPass.setPosition(330, 0);

	Block selector = Block(Color(255, 0, 0, 200), Color::Black, Vector2f(64, 64));
	selector.setPosition(-64, -64);

	GradeGenerator generator(selector);
	generator.setSound(selectSound, win);

	Event event; Mouse mouse; Clock clock;Clock clock2;
	float timer = 0, timer2 = 0;
	int x = 0, y = 0;
	srand(time(NULL));
	float animSpeed = 0;
	Text winnerText;
	winnerText.setFont(font);
	winnerText.setFillColor(Color::Black);
	winnerText.setPosition((640  - winnerText.getCharacterSize() * 4)/ 2, 300 / 2);
	winnerText.setString("TEST");
	bool activate = false;
	winnerText.setScale(0,0);
	animSpeed = 1;
	float moveX = trapCard.getPosition().x;
	Color randColor[] = { Color::Red,Color::Green,Color::Yellow };
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Vector2f mousePos = window.mapPixelToCoords(Vector2i(mouse.getPosition(window)));

		window.clear();

		if (button.isOver(mousePos))
		{
			button.setColor(Color::Red);
			if (mouse.isButtonPressed(mouse.Left))
			{
				generator.start();
				button.setColor(Color::Green);
			}
		}
		else  button.setColor(Color::White);

		if (notPass.getGlobalBounds().contains(mousePos) && !generator.winner) {
			if (animSpeed <= 1.5 && !activate) {
				animSpeed += (.02 * 2);
			}
			else activate = true;

			if (activate && animSpeed >= 1) {
				animSpeed -= (.05 * 2);
			}
			else activate = false;

			notPass.setScale(animSpeed, animSpeed);
		}
		else {
			notPass.setScale(1.1, .29);
		}

		generator.update();



		if (generator.winner)
		{
			timer += clock.restart().asSeconds();
			generator.selector_.getShape()->getPosition().x;
			int winX = generator.selector_.getShape()->getPosition().x / 64;
			int winY = (generator.selector_.getShape()->getPosition().y - 64) / 64;


			if (animSpeed <= 2 && !activate) {
				animSpeed += (.02 * 2);
				std::cout <<animSpeed<< std::endl;
			}
			else activate = true;

			if (activate && animSpeed >= 0.5) {
				animSpeed -= (.02 * 2);
			}
			else activate = false;
			winnerText.setScale(animSpeed, animSpeed);
			string temp = blocks[winY][winX].getString();
			winnerText.setString("WE HAVE A WINNER! \n        " + temp);
			winnerText.setPosition((640 - winnerText.getGlobalBounds().width) / 2, 600 / 2);

			if (timer > 0.000000000001)
			{

				blocks[rand() % 10][rand() % 10].setColor(Color::White);
				blocks[rand() % 10][rand() % 10].setColor(Color::Red);
				timer = 0;
			}
			timer2 += clock2.restart().asSeconds();
			if (timer2 > .06) {
				winnerText.setFillColor(randColor[rand()% 3]);
				timer2 = 0;
			}
		}
		else winnerText.setScale(0, 0);


		moveX -= 3;

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (notPass.getGlobalBounds().contains(mousePos)) {
					if (mouse.isButtonPressed(mouse.Left)) {
						blocks[i][j].getText()->setScale(.4, .5);
						blocks[i][j].getText()->setString("FAIL");

						trapCard.setPosition(moveX, trapCard.getPosition().y);

					}

				}
				if (button.isOver(mousePos))
				{
					if (mouse.isButtonPressed(mouse.Left))
					{
						int num = rand() % (100 - 40) + 40;
						blocks[i][j].getText()->setString(std::to_string(num));
					}
				}

				if (blocks[i][j].isOver(mousePos))
				{
					blocks[i][j].setColor(Color::Red);
				}
				else if (!generator.winner)
					blocks[i][j].setColor(Color::White);


				blocks[i][j].draw(window);
			}
		}

		generator.draw(window);
		button.draw(window);
		window.draw(notPass);

		window.draw(winnerText);
		window.draw(trapCard);
		window.display();
	}

	return 0;
}

void loadResources()
{

	if (!bWinner.loadFromFile("Assets/win_sound.ogg")) EXIT_FAILURE;
	if (!bSelect.loadFromFile("Assets/wheel_sound.ogg")) EXIT_FAILURE;
	if (!font.loadFromFile("Assets/emulogic.ttf"))EXIT_FAILURE;

	win.setBuffer(bWinner); win.setLoop(false);
	selectSound.setBuffer(bSelect); win.setLoop(false);
}
