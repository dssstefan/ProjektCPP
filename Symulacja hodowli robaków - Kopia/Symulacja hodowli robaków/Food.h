#pragma once
#include "Map.h"
#include "Spider.h"
#include "Options.h"

class Food
{
public:
	Food();
	~Food();

	void generateFood(Map &map);
	void draw(RenderWindow &window);
	void eaten(int i, int j, int cooldown);
	void update();
	int isEating(Spider spider, float cooldown);

	struct Circle: Options {
		CircleShape shape;
		bool active;
		float cooldownInSec = (float)*optionsVar[5];
	};

	vector <vector <Circle>> foods;
	vector <Circle*> foodsInCd;

private:
	Time lastUpdate;
	Clock time;
};

