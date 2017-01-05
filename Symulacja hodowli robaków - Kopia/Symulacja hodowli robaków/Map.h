#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "const.h"

using namespace std;
using namespace sf;

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
private:
	unsigned short width;
	unsigned short height;
	Tile getTile(short);
};

