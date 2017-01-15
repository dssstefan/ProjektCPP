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

	void update(vector <Spider> &spider, float *deltaTime, Map map);

	Face face;
	Vector2f movement;

private:
	void moveSpider(vector <Spider> &spider, float *deltaTime, Map map);
	void checkBorderCollision(Spider &spider, Map map);
	Face checkFace(Vector2f movement);


	float speed;
};

