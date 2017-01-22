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
	void death(float deltaTime);
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
	void grow(int count);
	void updateOptions();

	Vector2u textureSize;
	Animation animation;
	int wait;
	int random;
	float lifeTime;
	float minProductiveTime;
	float maxProductiveTime;
	float pregnacyTime;
	float hp;

private:
	Sprite sprite;
	float size;
	bool isMale;
	Vector2f movement;
	float maxMovement;
	Texture *texture;
};

