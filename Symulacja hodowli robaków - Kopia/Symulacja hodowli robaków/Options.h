#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Options
{
public:
	Options();
	~Options();

protected:
	int* optionsVar[10];
private:
	static int boardWidth;
	static int boardHeight;
	static int spiderQuantity;
	static int bornSpiderQuantity;
	static int health;
	static int foodRegeneration;
	static int maxSize;
	static int lifeTime;
	static int minProductiveTime;
	static int maxProductiveTime;
};