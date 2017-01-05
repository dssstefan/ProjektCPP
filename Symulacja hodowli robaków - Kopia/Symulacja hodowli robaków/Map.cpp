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
	fstream file;
	file.open("data/map.txt");

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
