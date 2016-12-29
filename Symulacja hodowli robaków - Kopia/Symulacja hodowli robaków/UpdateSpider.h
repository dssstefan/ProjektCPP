#pragma once
#include <SFML\Graphics.hpp>
#include "Spider.h"
#include <vector>

using namespace sf;
using namespace std;
class UpdateSpider
{
public:
	UpdateSpider(float speed);
	~UpdateSpider();

	void update(vector <Spider> &spider, float deltaTime);

	enum Position {
		LEFT, UP, RIGHT, DOWN
	};

	Position position;
	Vector2f movement;

private:
	float speed;
};

