#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Animation.h"
#include "Options.h"

using namespace sf;

class Spider: public Options
{
public:
	Spider();
	~Spider();

	void move(float x, float y, float deltTime, Face face);
	void move(float x, float y);
	void setPosition(float x, float y);
	void setTexture(Texture &t);
	void setTextureRect(IntRect);
	void addMovement(float x, float y);
	void setMovement(float x, float y);
	void setMale(bool);
	Vector2f getMovement();
	bool getMale();
	float getX();
	float getY();
	Collider getCollider();
	FloatRect getGlobalBounds();
	void draw(RenderWindow &window);

	Vector2u textureSize;
	Animation animation;
	int wait;
	int random;
private:
	int hp;
	int size;
	int lifeTime;
	int minProductiveTime;
	int maxProductiveTime;
	bool isMale;
	Vector2f movement;

	Texture *texture;
	Sprite sprite;

};

