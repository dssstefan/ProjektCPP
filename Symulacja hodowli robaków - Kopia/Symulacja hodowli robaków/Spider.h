#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
using namespace sf;

class Spider
{
public:
	Spider();
	~Spider();

	void move(float x, float y);
	void setPosition(float x, float y);
	void setTexture(sf::Texture &t);
	void setTextureRect(sf::IntRect);
	void addMovement(float x, float y);
	void setMovement(float x, float y);
	Vector2f getMovement();
	void draw(sf::RenderWindow &);
	void setMale(bool);
	float getX();
	float getY();
	Collider getCollider();
	FloatRect getGlobalBounds();
	Vector2u textureSize;
	int count;
	int random;
private:
	int hp;
	int size;
	bool isMale;
	Vector2f movement;

	Texture *texture;
	Sprite sprite;

};

