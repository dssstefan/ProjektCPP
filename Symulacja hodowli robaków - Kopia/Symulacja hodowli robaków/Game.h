#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Game
{
public:
	Game();
	~Game();

	void start();

protected:
	enum GameState {MENU, SETTINGS, PAUSE, GAME, GAME_OVER, END};
	GameState state;

private:
	sf::RenderWindow window;
	sf::Font font;
	//sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_WIDTH));
	void draw();
	void update(float);
	void game(sf::RenderWindow& window);
	void settings(sf::RenderWindow& window);
	void menu(sf::RenderWindow& window);
};

