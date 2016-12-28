#include "Spider.h"



Spider::Spider()
{
	hp = 30;
	texture = NULL;
}


Spider::~Spider()
{
}

void Spider::move(int x, int y)
{
	sprite.move(x, y);
}

void Spider::setPosition(int x, int y)
{
	sprite.setPosition(x, y);
}

void Spider::setTexture(sf::Texture &t)
{
	texture = &t;
	sprite.setTexture(*texture);
}

void Spider::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

float Spider::getX()
{
	return sprite.getPosition().x;
}

float Spider::getY()
{
	return sprite.getPosition().y;
}
