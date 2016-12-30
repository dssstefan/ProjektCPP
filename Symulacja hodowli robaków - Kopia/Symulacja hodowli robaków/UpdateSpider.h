#pragma once
#include <SFML\Graphics.hpp>
#include "Spider.h"
#include <vector>
#include "const.h"
#include "Map.h"

using namespace sf;
using namespace std;
class UpdateSpider
{
public:
	UpdateSpider(float speed);
	~UpdateSpider();

	void update(vector <Spider> &spider, float deltaTime, Map map);

	enum Position {
		LEFT, UP, RIGHT, DOWN
	};

	Position position;
	Vector2f movement;

private:
	void moveSpider(vector <Spider> &spider, float deltaTime, Map map);
	void checkCollision(Spider spider, Map map);

	float speed;
};

