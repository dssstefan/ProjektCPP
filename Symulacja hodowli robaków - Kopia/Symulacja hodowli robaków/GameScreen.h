#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


class GameScreen
{
public:
	GameScreen();
	~GameScreen();

	virtual void LoadContent(RenderWindow &window);
	virtual void UnloadContent();
	virtual void Update(RenderWindow &window, Event event);
	virtual void Draw(RenderWindow &window);
};

