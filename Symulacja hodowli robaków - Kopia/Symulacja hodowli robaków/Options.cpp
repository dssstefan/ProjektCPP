#include "Options.h"

int Options::boardWidth = 30;
int Options::boardHeight = 30;
int Options::spiderQuantity = 15;
int Options::bornSpiderQuantity = 1;
int Options::health = 10;
int Options::foodRegeneration = 10;
int Options::maxSize = 100;
int Options::lifeTime = 60;
int Options::minProductiveTime = 20;
int Options::maxProductiveTime = 50;

Options::Options()
{
	optionsVar[0] = &boardWidth;
	optionsVar[1] = &boardHeight;
	optionsVar[2] = &spiderQuantity;
	optionsVar[3] = &bornSpiderQuantity;
	optionsVar[4] = &health;
	optionsVar[5] = &foodRegeneration;
	optionsVar[6] = &maxSize;
	optionsVar[7] = &lifeTime;
	optionsVar[8] = &minProductiveTime;
	optionsVar[9] = &maxProductiveTime;
}

Options::~Options()
{
}
