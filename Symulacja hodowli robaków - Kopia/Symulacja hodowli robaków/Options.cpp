#include "Options.h"


Options::Options(int width, int height, int quantity, int bornQuantity, int h, int regeneration, int size, int life, int minp, int maxp)
{
	boardWidth = width;;
	boardHeight = height;
	spiderQuantity = quantity;
	bornSpiderQuantity = bornQuantity;
	health = h;
	foodRegeneration = regeneration;
	maxSize = size;
	lifeTime = life;
	minProductiveTime = minp;
	maxProductiveTime = maxp;

	value.resize(10);
	value[0] = &boardWidth;
	value[1] = &boardHeight;
	value[2] = &spiderQuantity;
	value[3] = &bornSpiderQuantity;
	value[4] = &health;
	value[5] = &foodRegeneration;
	value[6] = &maxSize;
	value[7] = &lifeTime;
	value[8] = &minProductiveTime;
	value[9] = &maxProductiveTime;
}

Options::~Options()
{
}
