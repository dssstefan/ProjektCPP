#include "CreateSpiders.h"
#include "const.h"
#include <random>

CreateSpiders::CreateSpiders()
{
	tSpiderM.loadFromFile("data/spider06.png");
	tSpiderF.loadFromFile("data/spider03.png");
	numberS = *optionsVar[2];
}


CreateSpiders::~CreateSpiders()
{
}

void CreateSpiders::createSpiders(vector <Spider> &spiderM, vector <Spider> &spiderF, unsigned short x, unsigned short y)
{
	random_device generator;
	uniform_int_distribution<int> randomX(0, x);
	uniform_int_distribution<int> randomY(0, y);
	uniform_int_distribution<int> rmovement(0, 100);

	spiderM.resize(numberS);
	spiderF.resize(numberS);

	for (int i = 0; i < numberS; i++)
	{
		
		spiderM[i].setPosition(randomX(generator) * TILE_SIZE, randomY(generator) * TILE_SIZE);
		spiderF[i].setPosition(randomX(generator) * TILE_SIZE, randomY(generator) * TILE_SIZE);
		spiderF[i].setMale(false);
		spiderF[i].pregnacyTime = 5;

		spiderM[i].setTexture(tSpiderM);
		spiderF[i].setTexture(tSpiderF);

		spiderM[i].textureSize = tSpiderM.getSize();
		spiderM[i].textureSize.x /= 7;
		spiderM[i].textureSize.y /= 5;
		spiderM[i].setTextureRect(sf::IntRect(spiderM[i].textureSize.x * 0, spiderM[i].textureSize.y * 2, spiderM[i].textureSize.x, spiderM[i].textureSize.y));
		spiderM[i].setMovement(rmovement(generator)/100, rmovement(generator)/100);
		spiderM[i].animation.setAnimation(&tSpiderM, Vector2u(7, 5), 0.03f);
		
		spiderF[i].textureSize = tSpiderF.getSize();
		spiderF[i].textureSize.x /= 7;
		spiderF[i].textureSize.y /= 5;
		spiderF[i].setTextureRect(sf::IntRect(spiderF[i].textureSize.x * 0, spiderF[i].textureSize.y * 2, spiderF[i].textureSize.x, spiderF[i].textureSize.y));
		spiderF[i].setMovement(rmovement(generator)/100, rmovement(generator)/100);
		spiderF[i].animation.setAnimation(&tSpiderF, Vector2u(7, 5), 0.03f);
	}
}

Spider CreateSpiders::addSpider(bool isMale, Vector2f position)
{
	random_device generator;
	uniform_int_distribution<int> rmovement(0, 100);

	Spider newSpider;

	newSpider.setPosition(position.x, position.y);
	newSpider.setMale(isMale);
	if (newSpider.getMale())
	{
		newSpider.setTexture(tSpiderM);
		newSpider.textureSize = tSpiderM.getSize();
	}
	else
	{
		newSpider.setTexture(tSpiderF);
		newSpider.textureSize = tSpiderF.getSize();
	}

	newSpider.textureSize.x /= 7;
	newSpider.textureSize.y /= 5;
	newSpider.setTextureRect(sf::IntRect(newSpider.textureSize.x * 0, newSpider.textureSize.y * 2, newSpider.textureSize.x, newSpider.textureSize.y));
	newSpider.animation.setAnimation(&tSpiderM, Vector2u(7, 5), 0.03f);
	newSpider.setMovement(rmovement(generator) / 100, rmovement(generator) / 100);
	return newSpider;
}
