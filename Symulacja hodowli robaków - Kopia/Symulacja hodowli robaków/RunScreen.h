#pragma once
#include "ScreenManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.h"
#include "Spider.h"
#include "CreateSpiders.h"
#include "UpdateSpider.h"
#include "Food.h"
#include "const.h"
#include "Options.h"

using namespace std;
using namespace sf;

class RunScreen : public GameScreen, public Options
{
public:
	RunScreen();
	~RunScreen();

	void LoadContent(RenderWindow &window);
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);

private:
	void setMap(string string, RenderWindow &window);
	void updateMap();
	void update(float);
	View view;
	Time lastUpdate;
	Clock time;
	int WIDTH;
	int HEIGHT;
	int TRUEWIDTH;
	int TRUEHEIGHT;
	Texture texture[12];
	Map map;
	vector<vector<Sprite>> sprite;

	Vector2f camera;

	CreateSpiders createSpiders;
	vector <Spider> spiderM;
	vector <Spider> spiderF;

	UpdateSpider updatespider;
	Food nourishment;
};

