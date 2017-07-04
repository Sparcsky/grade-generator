#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Block
{
public:
	Block(Color fill, Color border, Vector2f size);
	Block();
	~Block();

	bool isOver(Vector2f position);

	void textSettings(std::string title, Font & font, float scale, Color fill);
	void setPosition(int x, int y);
	void setTextPosition(int x, int y);
	void draw(RenderWindow &window);
	void setColor(Color color);
	int textSize() { return text.getCharacterSize(); }

	std::string getString() { return text.getString(); }

	RectangleShape * getShape() { return &shape; }
	Text* getText() { return &text; }

private:
	Text text;
	RectangleShape shape;
	bool winner = false;
};

