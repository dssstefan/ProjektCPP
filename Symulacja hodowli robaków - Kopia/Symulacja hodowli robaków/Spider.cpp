#include "Spider.h"



Spider::Spider()
{
	hp = 30;
	texture = NULL;
	isMale = true;
	textureSize.x = 0;
	textureSize.y = 0;
}


Spider::~Spider()
{
}

void Spider::move(float x, float y)
{
	sprite.move(x, y);
}

void Spider::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Spider::setTexture(sf::Texture &t)
{
	texture = &t;
	sprite.setTexture(*texture);
}

void Spider::setTextureRect(sf::IntRect Rect)
{
	sprite.setTextureRect(Rect);
}

void Spider::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Spider::setMale(bool t)
{
	isMale = t;
}

float Spider::getX()
{
	return sprite.getPosition().x;
}

float Spider::getY()
{
	return sprite.getPosition().y;
}
