#pragma once
#include <SFML\Graphics.hpp>
#include "Spider.h"

using namespace sf;

class Collider
{
public:
public:
	Collider(Vector2f size, Vector2f position);
	Collider(Spider spider);
	~Collider();

	void Move(float dx, float dy);

	bool CheckCollision(Collider& other, float push);
	sf::Vector2f GetPosition();
	sf::Vector2f GetHalfSize();


private:
	sf::RectangleShape body;
};

