#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"


/*
void ResizedView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(SCRN_HEIGHT * aspectRatio, SCRN_WIDTH);
}
*/
int main()
{

	Game game;
	game.start();
	
	return 0;
}