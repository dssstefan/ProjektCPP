#include "CreateSpiders.h"
#include "const.h"


CreateSpiders::CreateSpiders()
{
	tSpiderM.loadFromFile("data/spider06.png");
	tSpiderF.loadFromFile("data/spider03.png");
}


CreateSpiders::~CreateSpiders()
{
}

void CreateSpiders::createSpiders(vector <Spider> &spiderM, vector <Spider> &spiderF, unsigned short x, unsigned short y)
{

	spiderM.resize(15);
	spiderF.resize(15);

	for (int i = 0; i < 15; i++)
	{
		
		spiderM[i].setPosition(rand()% x * TILE_SIZE, rand() % y * TILE_SIZE);
		spiderF[i].setPosition(rand() % x * TILE_SIZE, rand() % y * TILE_SIZE);
		spiderF[i].setMale(false);
		
		spiderM[i].setTexture(tSpiderM);
		spiderF[i].setTexture(tSpiderF);

		spiderM[i].textureSize = tSpiderM.getSize();
		spiderM[i].textureSize.x /= 7;
		spiderM[i].textureSize.y /= 5;
		spiderM[i].setTextureRect(sf::IntRect(spiderM[i].textureSize.x * 0, spiderM[i].textureSize.y * 2, spiderM[i].textureSize.x, spiderM[i].textureSize.y));

		spiderF[i].textureSize = tSpiderF.getSize();
		spiderF[i].textureSize.x /= 7;
		spiderF[i].textureSize.y /= 5;
		spiderF[i].setTextureRect(sf::IntRect(spiderF[i].textureSize.x * 0, spiderF[i].textureSize.y * 2, spiderF[i].textureSize.x, spiderF[i].textureSize.y));
	}
}
