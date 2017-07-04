#include "Block.h"


Block::Block(Color fill, Color border, Vector2f size)
{
	shape.setFillColor(fill);
	shape.setOutlineColor(border);
	shape.setOutlineThickness(5);
	shape.setSize(size);
}


Block::Block()
{
}

Block::~Block()
{
}

bool Block::isOver(Vector2f position)
{
	if (shape.getGlobalBounds().contains(position))
	{
		return true;
	}
	return false;
}

void Block::textSettings(std::string title, Font & font,float scale,Color fill)
{
	text.setString(title);
	text.setScale(scale,scale);
	text.setFillColor(fill);
	text.setFont(font);
	text.setFillColor(Color::Black);
}


void Block::setPosition(int x, int y)
{
	shape.setPosition(x, y);
}

void Block::setTextPosition(int x, int y)
{
	text.setPosition(x + (text.getGlobalBounds().width - textSize() / 2) / 2, y + (text.getGlobalBounds().height + textSize()) / 2);

}

void Block::draw(RenderWindow & window)
{
	window.draw(shape);
	window.draw(text);
}

void Block::setColor(Color color)
{
	shape.setFillColor(color);
}
