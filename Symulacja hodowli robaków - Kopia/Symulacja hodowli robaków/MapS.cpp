#include "MapS.h"
#include <fstream>

MapS::MapS()
{
	width = 0;
	height = 0;
}

MapS & MapS::GetInstace()
{
	static MapS instance;
	return instance;
}

MapS::~MapS()
{
}

void MapS::loadMap()
{
	Texture t;
	t.loadFromFile("data/empty.png");
	width = *optionsVar[0];
	height = *optionsVar[1];
	tileMap.resize(height);

	for (int i = 0; i < height; i++)
	{
		tileMap[i].resize(width);
	}

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			tileMap[y][x] = getTile(0);
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

}

void MapS::updateMap()
{
	int x = 0;
	if (width != *optionsVar[0] || height != *optionsVar[1])
	{
		if (width >= *optionsVar[0] && height >= *optionsVar[1])
			x = 1;
		else if (width == *optionsVar[0] && height >= *optionsVar[1])
			x = 2;
		else if (width >= *optionsVar[0] && height == *optionsVar[1])
			x = 3;
		else if (width <= *optionsVar[0] && height <= *optionsVar[1])
			x = 4;
		else if (width <= *optionsVar[0] && height >= *optionsVar[1])
			x = 5;
		else if (width >= *optionsVar[0] && height <= *optionsVar[1])
			x = 6;
	}

	switch (x)
	{
	case 1:
		tileMap.resize(*optionsVar[1]);
		for (int i = 0; i < *optionsVar[1]; i++)
		{
			tileMap[i].resize(*optionsVar[0]);
		}

		for (int y = 0; y < *optionsVar[1]; y++)
		{
			for (int x = width; x < *optionsVar[0] && y < height; x++)
			{
				tileMap[y][x] = getTile(0);
			}

			for (int x = 0; x < *optionsVar[0] && y >=height; x++)
			{
				tileMap[y][x] = getTile(0);
			}
		}
		break;
	case 2:
		tileMap.resize(*optionsVar[1]);
		for (int i = height; i < *optionsVar[1]; i++)
		{
			tileMap[i].resize(width);
		}
		for (int y = height; y < *optionsVar[1]; y++)
		{
			for (int x = 0; x < width; x++)
			{
				tileMap[y][x] = getTile(0);
			}
		}
		break;
	case 3:
		for (int i = 0; i < height; i++)
		{
			tileMap[i].resize(*optionsVar[0]);
		}
		for (int y = height; y < height; y++)
		{
			for (int x = width; x < *optionsVar[0]; x++)
			{
				tileMap[y][x] = getTile(0);
			}
		}
		break;
	case 4:
		for (int i = 0; i < height; i++)
		{
			for (int j = *optionsVar[0]; j < width; j++)
			{
				tileMap[i].pop_back();
			}
		}
		for (int i = *optionsVar[1]; i < height; i++)
		{
			tileMap.pop_back();
		}
		break;
	case 5:
		tileMap.resize(*optionsVar[1]);
		for (int i = 0; i < *optionsVar[1]; i++)
		{
			for (int j = *optionsVar[0]; j < width && i < height; j++)
			{
				tileMap[i].pop_back();
			}
			for (int j = 0; j < *optionsVar[0] && i >= height; j++)
			{
				tileMap[i].resize(*optionsVar[0]);
			}
		}

		for (int y = height; y < *optionsVar[1]; y++)
		{
			for (int x = 0; x < *optionsVar[0]; x++)
			{
				tileMap[y][x] = getTile(0);
			}
		}
		break;
	case 6:
		for (int i = 0; i < *optionsVar[1]; i++)
		{
			tileMap[i].resize(*optionsVar[0]);
		}
		for (int i = *optionsVar[1]; i < height; i++)
		{
			tileMap.pop_back();
		}

		for (int y = 0; y < *optionsVar[1]; y++)
		{
			for (int x = width; x < *optionsVar[0]; x++)
			{
				tileMap[y][x] = getTile(0);
			}
		}
		break;
	default:
		break;
	}
	height = *optionsVar[1];
	width = *optionsVar[0];
}

void MapS::changeTile(unsigned short x, unsigned short y)
{
	switch (tileMap[y][x].type)
	{
	case GRASS_1:
		tileMap[y][x] = getTile(1);
		break;
	case SAND_1:
		tileMap[y][x] = getTile(2);
		break;
	case BUSH:
		tileMap[y][x] = getTile(0);
		break;
	default:
		break;
	}
}

void MapS::updateTileC()
{
	Texture t;
	t.loadFromFile("data/empty.png");

	if(tileC.size() > 0)
		tileC.clear();

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
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
}

unsigned short MapS::getWidth()
{
	return width;
}

unsigned short MapS::getHeight()
{
	return height;
}

Collider MapS::getCollider(Sprite &sprite)
{
	return Collider(sprite);
}

MapS::Tile MapS::getTile(short code)
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
