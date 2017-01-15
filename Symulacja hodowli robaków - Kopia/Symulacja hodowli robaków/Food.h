#pragma once
#include "Map.h"
#include "Spider.h"
class Food
{
public:
	Food();
	~Food();

	void generateFood(Map &map);
	void draw(RenderWindow &window);
	void eaten(int i, int j, int cooldown);
	void update(float *deltaTime);
	int isEating(Spider spider, float cooldown);

	struct Circle {
		CircleShape shape;
		bool active;
		float cooldownInSec = 30;
	};

	vector <vector <Circle>> foods;
	vector <Circle*> foodsInCd;

private:

};

