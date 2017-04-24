#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "const.h"
#include "Collider.h"
#include "Options.h"
using namespace std;
using namespace sf;

class Map: public Options
{
public:
	Map();
	~Map();

	bool loadFromFile();
	void loadMap();
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

