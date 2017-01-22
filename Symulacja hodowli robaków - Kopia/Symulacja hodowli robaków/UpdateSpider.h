#pragma once
#include <SFML\Graphics.hpp>
#include "Spider.h"
#include <vector>
#include "const.h"
#include "MapS.h"

using namespace sf;
using namespace std;
class UpdateSpider
{
public:
	UpdateSpider(float speed);
	~UpdateSpider();

	void update(vector <Spider> &spider, vector <Spider> &deadSpider, float deltaTime);

	Face face;
	Vector2f movement;

private:
	void moveSpider(vector <Spider> &spider,float deltaTime);
	void checkBorderCollision(Spider &spider);
	Face checkFace(Vector2f movement);
	Time lastUpdate;
	Clock time;
	float delta;
	float speed;
};

