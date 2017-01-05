#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;

class Collider
{
public:
	Collider(Sprite & sprite);
	~Collider();

	void Move(float dx, float dy);

	bool CheckCollision(Collider& other, float push);
	Vector2f GetPosition();
	Vector2f GetHalfSize();


private:
	Sprite & body;
};

