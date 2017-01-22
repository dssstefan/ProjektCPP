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

class MapS : public Options
{
public:
	static MapS &GetInstace();
	~MapS();

	void loadMap();
	void updateMap();
	void changeTile(unsigned short x, unsigned short y);
	void updateTileC();
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

	MapS();
	MapS(MapS const&);
};

