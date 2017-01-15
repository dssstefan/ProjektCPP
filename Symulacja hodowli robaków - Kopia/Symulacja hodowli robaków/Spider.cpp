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

void Spider::move(float x, float y, float deltaTime, Face face)
{
	animation.update( deltaTime, face);
	sprite.setTextureRect(animation.uvRect);
	sprite.move(x, y);
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

	if (movement.x > 3)
		movement.x = 3;
	else if (movement.x < -3)
		movement.x = -3;

	if (movement.y > 3)
		movement.y = 3;
	else if (movement.y < -3)
		movement.y = -3;

}

void Spider::setMovement(float x, float y)
{
	movement.x = x;
	movement.y = y;

	if (movement.x > 3)
		movement.x = 3;
	else if (movement.x < -3)
		movement.x = -3;

	if (movement.y > 3)
		movement.y = 3;
	else if (movement.y < -3)
		movement.y = -3;
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

bool Spider::getMale()
{
	return isMale;
}

float Spider::getX()
{
	return sprite.getPosition().x;
}

float Spider::getY()
{
	return sprite.getPosition().y;
}

FloatRect Spider::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}


Collider Spider::getCollider()
{
	return Collider(sprite);
}


