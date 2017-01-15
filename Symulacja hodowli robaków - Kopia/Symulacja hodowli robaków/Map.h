#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "const.h"
#include "Collider.h"
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
	Collider getCollider(Sprite & sprite);

	struct Tile {
		TileType type;

		bool collideable;
		bool interactable;
	};

	vector < vector <Tile > > tileMap;
	vector <Sprite> tileC;
private:
	unsigned short width;
	unsigned short height;
	Tile getTile(short);
};

