#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
static const float VIEW_HEIGHT = 1024.0f;
static const float VIEW_WIDTH = 1024.0f;


void ResizedView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_WIDTH);
}

int main()
{

	Game game;
	game.start();
	

	return 0;
}