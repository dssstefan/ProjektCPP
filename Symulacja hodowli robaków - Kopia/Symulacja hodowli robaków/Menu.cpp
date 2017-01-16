#include "Menu.h"
#include "const.h"


Menu::Menu() 
{
	window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Symulacja hodowli robaków", Style::Close);
	view.setSize(SCRN_WIDTH, SCRN_HEIGHT);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGHT / 2);

	state = END;
	if (!font.loadFromFile("data/AmaticSC-Regular.ttf"))
	{
		cout << "Font not found!";
		return;
	}
	state = MENU;
}


Menu::~Menu()
{
}

void Menu::start()
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


void Menu::draw()
{
}

void Menu::game(sf::RenderWindow & window)
{
}

void Menu::settings(sf::RenderWindow & window)
{
}

void Menu::menu(sf::RenderWindow& window)
{
	Vector2u windowSize = window.getSize();
	Text title("Symulacja Hodowli Robaków", font, 80);
	title.setStyle(sf::Text::Bold);

	title.setPosition(windowSize.x / 2 - title.getGlobalBounds().width / 2, 20);

	const int number = 3;

	Text text[number];

	string str[] = { "Start", "Ustawienia", "Wyjscie" };

	for (int i = 0; i < number; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setString(str[i]);
		text[i].setPosition(windowSize.x / 2 - text[i].getGlobalBounds().width / 2, 2 * windowSize.y / 7 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(sf::Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				state = END;
			}
			else if (text[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased  && event.key.code == Mouse::Left)
			{
				state = END;
			}


			if (text[0].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased  && event.key.code == Mouse::Left)
			{
				state = GAME;
			}
			else if (text[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased  && event.key.code == Mouse::Left)
			{
				state = SETTINGS;
			}
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
