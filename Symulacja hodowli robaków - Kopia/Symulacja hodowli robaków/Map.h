#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	~Map();

	bool loadFromFile();
	unsigned short getWidth();
	unsigned short getHeight();
	enum TileType {
		GRASS_1, SAND_1, SAND_2, GRASS_2, GRASS_3, GRASS_4, 
		GRASS_5, GRASS_6, GRASS_7, GRASS_8, GRASS_9, BUSH
	};

	struct Tile {
		TileType type;

		bool collideable;
		bool interactable;
	};

	vector < vector <Tile > > tilemap;
private:
	unsigned short width;
	unsigned short height;
	Tile getTile(short);
};

