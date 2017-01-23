#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ScreenManager.h"
#include "const.h"
#include "MapS.h"
using namespace sf;

int main()
{
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
		window.pollEvent(event);
		window.clear();
		ScreenManager::GetInstance().Update(window, event);
		ScreenManager::GetInstance().Draw(window);
		window.display();
	}

	return 0;
}