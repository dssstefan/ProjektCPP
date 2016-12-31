#include "Spider.h"



Spider::Spider()
{
	hp = 30;
	texture = NULL;
	isMale = true;
	textureSize.x = 0;
	textureSize.y = 0;
	count = 0;
	random = 0;
	movement.x = 0;
	movement.y = 0;
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

void Spider::addMovement(float x, float y)
{
	movement.x += x;
	movement.y += y;

	if (movement.x > 1)
		movement.x = 1;
	else if (movement.x < -1)
		movement.x = -1;
	
	if (movement.y > 1)
		movement.y = 1;
	else if (movement.y < -1)
		movement.y = -1;

}

void Spider::setMovement(float x, float y)
{
	movement.x = x;
	movement.y = y;

	if (movement.x > 1)
		movement.x = 1;
	else if (movement.x < -1)
		movement.x = -1;

	if (movement.y > 1)
		movement.y = 1;
	else if (movement.y < -1)
		movement.y = -1;
}

sf::Vector2f Spider::getMovement()
{
	return movement;
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
