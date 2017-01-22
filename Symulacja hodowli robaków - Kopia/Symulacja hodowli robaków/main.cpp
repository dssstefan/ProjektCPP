#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScreenManager.h"
#include "const.h"
#include "MapS.h"
using namespace sf;

/*
void ResizedView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(SCRN_HEIGHT * aspectRatio, SCRN_WIDTH);
}
*/
int main()
{

	/*Game game;
	game.start();*/
	RenderWindow window(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Symulacja hodowli robaków", Style::Close);
	View view;
	view.setSize(SCRN_WIDTH, SCRN_HEIGHT);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGHT / 2);
	window.setView(view);
	window.setFramerateLimit(240);
	Options options;
	ScreenManager::GetInstance().Initialize();
	ScreenManager::GetInstance().LoadContent(window);
	MapS::GetInstace().loadMap();

	while (window.isOpen())
	{
		Event event;
		if(window.pollEvent(event))
		{
			/*if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}*/

			
		}
		window.clear();

		ScreenManager::GetInstance().Update(window, event);
		ScreenManager::GetInstance().Draw(window);
		window.display();

	}

	return 0;
}