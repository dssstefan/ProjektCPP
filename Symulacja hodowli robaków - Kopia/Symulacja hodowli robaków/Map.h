#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "const.h"

using namespace std;

class Map
{
public:
	Map();
	~Map();

	bool loadFromFile();
	unsigned short getWidth();
	unsigned short getHeight();
	

	struct Tile {
		TileType type;

		bool collideable;
		bool interactable;
	};

	vector < vector <Tile > > tileMap;
	vector <Tile > tileMapColl;
	vector <Tile > tileMapInt;
private:
	unsigned short width;
	unsigned short height;
	Tile getTile(short);
};

