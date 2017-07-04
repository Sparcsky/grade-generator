#include "GradeGenerator.h"
#include <iostream>
GradeGenerator::GradeGenerator(Block &selector)
	:selector_(selector)
{

}

GradeGenerator::~GradeGenerator()
{
}

void GradeGenerator::reset()
{
	generate = false;
	selectSound_.stop();


}

void GradeGenerator::start()
{
	generate = true;
	selector_.setColor(Color(255, 0, 0, 200));
	selectSound_.play();
	selectSound_.setPlayingOffset(sf::seconds(3));
	delay = .1f;
	winSound_.stop();
	winner = false;
}

void GradeGenerator::update()
{

	if (generate)
	{
		timer += clock.restart().asSeconds();

		if (timer > delay)
		{
			timer = 0;

			int randX = (rand() % 10) * 64;
			int randY = (rand() % 10 + 1) * 64;

			if (selectSound_.getStatus() != selectSound_.Playing) {
				selector_.setColor(Color(0, 255, 0, 200));
				reset();
				std::cout << "RUNNING" << std::endl;
				winSound_.play();
				winner = true;
			}
			else {
				selector_.setPosition(randX, randY);

			}
			if (selectSound_.getPlayingOffset().asSeconds() <= 5) delay = .1;
			else if (selectSound_.getPlayingOffset().asSeconds() <= 7) delay = .4;
			else if (selectSound_.getPlayingOffset().asSeconds() <= 9) delay = .75;
			else if (selectSound_.getPlayingOffset().asSeconds() <= 10.6)
			{
				delay = 1;
			}

		

		}
	}
}

void GradeGenerator::setSound(Sound & select, Sound & winSound)
{
	selectSound_ = select;
	winSound_ = winSound;
	winSound_.setPlayingOffset(sf::seconds(1));
}

void GradeGenerator::draw(RenderWindow & window)
{
	selector_.draw(window);
}
