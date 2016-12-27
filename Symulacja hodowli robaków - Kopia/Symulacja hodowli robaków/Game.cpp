#include "Game.h"



Game::Game():
	window(sf::VideoMode(1024, 1024), "Symulacja hodowli robaków", sf::Style::Close | sf::Style::Resize)
{	
	state = END;

	if (!font.loadFromFile("data/AmaticSC-Regular.ttf"))
	{
		std::cerr << "Font not found!";
		return;
	}
	
	state = MENU;
	
}


Game::~Game()
{
}

void Game::start()
{
	while (state != END)
	{
		
		switch (state)
		{
		case GameState::MENU:
			menu(window);
			break;
		case GameState::GAME:
			game(window);
			break;
		case GameState::SETTINGS:
			settings(window);
			break;
		}
	}

}


void Game::draw()
{
}

void Game::update(float)
{
}

void Game::game(sf::RenderWindow & window)
{
}

void Game::settings(sf::RenderWindow & window)
{
}

void Game::menu(sf::RenderWindow& window)
{
	sf::Vector2u windowSize = window.getSize();
	sf::Text title("Symulacja Hodowli Robaków", font, 80);
	title.setStyle(sf::Text::Bold);

	title.setPosition(windowSize.x/ 2 - title.getGlobalBounds().width / 2, 20);

	const int number = 3;
	
	sf::Text text[number];

	std::string str[] = { "Start", "Ustawienia", "Wyjscie" };

	for (int i = 0; i < number; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setString(str[i]);
		text[i].setPosition(windowSize.x/2 - text[i].getGlobalBounds().width / 2, 2 * windowSize.y / 7 + i * 120);
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				state = END;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased  && event.key.code == sf::Mouse::Left)
			{
				state = END;
			}

			if (text[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased  && event.key.code == sf::Mouse::Left)
				game(window);

			if (text[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased  && event.key.code == sf::Mouse::Left)
				settings(window);
		}

		for (int i = 0; i < number; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(sf::Color::Green);
			else
				text[i].setFillColor(sf::Color::White);

		window.clear();

		window.draw(title);
		for (int i = 0; i < number; i++)
		window.draw(text[i]);
		window.display();
	}

}
