#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "InputManager.h"

using namespace std;
using namespace sf;


class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void LoadContent();
	virtual void UnloadContent();
	virtual void Update(RenderWindow &window, Event event);
	virtual void Draw(RenderWindow &window);

protected:
	InputManager input;
	vector<int> keys;
};

