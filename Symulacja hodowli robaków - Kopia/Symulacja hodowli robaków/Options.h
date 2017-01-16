#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Options
{
public:
	Options(int width = 30,
	int height = 30,
	int quantity = 30,
	int bornQuantity = 1,
	int h = 10,
	int regeneration = 10,
	int size = 100,
	int life = 60,
	int minp = 20,
	int maxp = 50);
	~Options();

protected:
	int boardWidth;
	int boardHeight;
	int spiderQuantity;
	int bornSpiderQuantity;
	int health;
	int foodRegeneration;
	int maxSize;
	int lifeTime;
	int minProductiveTime;
	int maxProductiveTime;

	vector <int*> value;
};

