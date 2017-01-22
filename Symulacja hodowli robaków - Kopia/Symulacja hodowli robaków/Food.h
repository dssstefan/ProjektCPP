#pragma once
#include "Spider.h"
#include "Options.h"
#include "MapS.h"

class Food
{
public:
	Food();
	~Food();

	void generateFood();
	void draw(RenderWindow &window);
	void eaten(int i, int j, int cooldown);
	void update(float deltaTime);
	int isEating(Spider spider, float cooldown);

	struct Circle: Options {
		CircleShape shape;
		bool active;
		float cooldownInSec = (float)*optionsVar[5];
	};

	vector <vector <Circle>> foods;
	vector <Circle*> foodsInCd;
};