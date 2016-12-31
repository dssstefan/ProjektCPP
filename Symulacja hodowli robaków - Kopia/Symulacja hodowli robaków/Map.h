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
	
	struct TileC {
		TileType type;

		bool collideable;
		Vector2f position;
	};

	struct TileI {
		TileType type;

		bool interactable;
		Vector2f position;
	};


	struct Tile {
		TileType type;

		bool collideable;
		bool interactable;
	};

	vector < vector <Tile > > tileMap;
	vector <TileC > tileMapColl;
	vector <TileI > tileMapInt;
private:
	unsigned short width;
	unsigned short height;
	Tile getTile(short);
};

