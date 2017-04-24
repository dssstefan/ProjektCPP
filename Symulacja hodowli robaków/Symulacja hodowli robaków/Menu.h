#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();
	void start();

protected:
	enum GameState { MENU, SETTINGS, PAUSE, GAME, GAME_OVER, END };
	GameState state;

	RenderWindow window;
	Font font;
	View view;

private:
	void draw();
	void game(RenderWindow& window);
	void settings(RenderWindow& window);
	void menu(RenderWindow& window);

};

