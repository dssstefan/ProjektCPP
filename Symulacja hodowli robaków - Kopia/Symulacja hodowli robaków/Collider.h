#pragma once
#include <SFML\Graphics.hpp>


using namespace sf;

class Collider
{
public:
	Collider(Sprite & sprite);
	Collider(Vector2f position, Vector2f size);
	~Collider();

	void Move(float dx, float dy);

	bool CheckCollision(Collider& other, float push);
	Vector2f GetPosition();
	Vector2f GetHalfSize();


private:
	Sprite & body;
	Sprite sp;
	Vector2f postition;
	Vector2f size;
};

