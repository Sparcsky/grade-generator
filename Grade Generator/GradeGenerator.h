#pragma once
#include <SFML\Audio.hpp>
#include "Block.h"
using namespace sf;
class GradeGenerator
{
public:
	Block selector_;
	bool winner = false;

	GradeGenerator(Block &selector);
	~GradeGenerator();

	void reset();
	void start();
	void update();
	void setSound(Sound & select, Sound & winSound);
	void draw(RenderWindow &window);
private:
	Sound winSound_, selectSound_;
	float timer = 0, delay = .1f;
	bool generate = false;
	Clock clock;
};

