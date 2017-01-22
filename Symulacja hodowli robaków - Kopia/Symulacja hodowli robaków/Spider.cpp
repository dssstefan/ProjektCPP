#include "Spider.h"



Spider::Spider()
{
	hp = *optionsVar[4];
	lifeTime = *optionsVar[7];
	minProductiveTime = *optionsVar[8];
	maxProductiveTime = *optionsVar[9];
	size = *optionsVar[6];
	size /= 100;
	texture = NULL;
	isMale = true;
	textureSize.x = 0;
	textureSize.y = 0;
	wait = 0;
	random = 0;
	movement.x = 0;
	movement.y = 0;
	maxMovement = 1;
	pregnacyTime = 0;
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

void Spider::death(float deltaTime)
{
	animation.dead(deltaTime);
	sprite.setTextureRect(animation.uvRect);
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

	if (movement.x > maxMovement)
		movement.x = maxMovement;
	else if (movement.x < -maxMovement)
		movement.x = -maxMovement;

	if (movement.y > maxMovement)
		movement.y = maxMovement;
	else if (movement.y < -maxMovement)
		movement.y = -maxMovement;

}

void Spider::setMovement(float x, float y)
{
	movement.x = x;
	movement.y = y;

	if (movement.x > maxMovement)
		movement.x = maxMovement;
	else if (movement.x < -maxMovement)
		movement.x = -maxMovement;

	if (movement.y > maxMovement)
		movement.y = maxMovement;
	else if (movement.y < -maxMovement)
		movement.y = -maxMovement;

	wait = 0;
}

sf::Vector2f Spider::getMovement()
{
	return movement;
}

void Spider::draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Spider::grow(int count)
{
	updateOptions();
	if (sprite.getScale().x < size)
	{
		sprite.setScale(sprite.getScale().x + count *0.01, sprite.getScale().y + count *0.01);
	}
}

void Spider::updateOptions()
{
	hp = *optionsVar[4];
	lifeTime = *optionsVar[7];
	minProductiveTime = *optionsVar[8];
	maxProductiveTime = *optionsVar[9];
	size = *optionsVar[6];
	size /= 100;
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


