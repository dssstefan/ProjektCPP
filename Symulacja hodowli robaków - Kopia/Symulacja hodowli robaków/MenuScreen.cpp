#include "MenuScreen.h"
#include "const.h"


MenuScreen::MenuScreen()
{
}


MenuScreen::~MenuScreen()
{
}

void MenuScreen::LoadContent()
{
	if (!font.loadFromFile("data/AmaticSC-Regular.ttf"))
	{
		cout << "Font not found" << endl;
	}
	title.setFont(font);
	title.setString("Symulacja Hodowli Robaków");
	title.setStyle(sf::Text::Bold);
	title.setCharacterSize(80);
	title.setPosition(SCRN_WIDTH / 2 - title.getGlobalBounds().width / 2, 20);

	string str[] = { "Start", "Ustawienia", "Wyjœcie" };

	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setString(str[i]);
		text[i].setPosition(SCRN_WIDTH  / 2 - text[i].getGlobalBounds().width / 2, 2 * SCRN_HEIGHT / 7 + i * 120);
	}

	click = Mouse::Left;
}

void MenuScreen::UnloadContent()
{
	GameScreen::UnloadContent();
	click = NULL;
}

void MenuScreen::Update(RenderWindow &window, Event event)
{
	input.Update(window, event);
	Vector2f mouse(sf::Mouse::getPosition(window));

	for (int i = 0; i < 3; i++)
		if (text[i].getGlobalBounds().contains(mouse))
			text[i].setFillColor(Color::Green);
		else
			text[i].setFillColor(Color::White);

	if (input.MouseLeftReleased(click) && text[0].getGlobalBounds().contains(mouse))
	{
		ScreenManager::GetInstance().AddScreen(new RunScreen);
	}
	else if (input.MouseLeftReleased(click) && text[1].getGlobalBounds().contains(mouse))
	{
		ScreenManager::GetInstance().AddScreen(new SettingsScreen);
	}
	else if (input.MouseLeftReleased(click) && text[2].getGlobalBounds().contains(mouse))
	{
		window.close();
	}
}

void MenuScreen::Draw(RenderWindow & window)
{
	window.draw(title);
	for (int i = 0; i < 3; i++)
		window.draw(text[i]);

}
