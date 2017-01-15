#include "Map.h"
#include <fstream>


Map::Map()
{
	width = 0;
	height = 0;
}


Map::~Map()
{
}

bool Map::loadFromFile()
{
	int s=0;
	fstream file;
	file.open("data/map.txt");

	Texture t;
	t.loadFromFile("data/empty.png");

	if (!file.is_open())
		return false;

	file >> height >> width;

	if (width == 0 || height == 0)
	{
		file.close();
		return false;
	}

	tileMap.resize(height);

	for (int i = 0; i < height; i++)
	{
		tileMap[i].resize(width);
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			short buffer;
			file >> buffer;
			tileMap[y][x] = getTile(buffer);
			if (tileMap[y][x].collideable)
			{
				Sprite tileSprite; 
			
				tileSprite.setTexture(t);
				tileSprite.setTextureRect(IntRect(0, 0, TILE_SIZE, TILE_SIZE));
				tileSprite.setPosition(TILE_SIZE * x, TILE_SIZE * y);
				tileC.push_back(tileSprite);
			}
		}

	}

	file.close();
	return true;
}

unsigned short Map::getWidth()
{
	return width;
}

unsigned short Map::getHeight()
{
	return height;
}

Collider Map::getCollider(Sprite &sprite)
{
	return Collider(sprite);
}

Map::Tile Map::getTile(short code)
{
	Tile tile;
	tile.type = TileType(code);

	switch (TileType(code))
	{
	case SAND_1:
		tile.collideable = false;
		tile.interactable = false;
		break;
	case SAND_2:
		tile.collideable = false;
		tile.interactable = false;
		break;
	case BUSH:
		tile.collideable = true;
		tile.interactable = false;
		break;
	default:
		tile.collideable = false;
		tile.interactable = true;
		break;
	}

	return tile;
}
