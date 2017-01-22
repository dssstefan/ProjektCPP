#include "MenuScreen.h"
#include "const.h"

MenuScreen::MenuScreen()
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::LoadContent(RenderWindow &window)
{
	if (!fontTitle.loadFromFile("data/Aleo-Regular.otf"))
	{
		cout << "Font not found" << endl;
	}
	if (!font.loadFromFile("data/Aleo-Regular.otf"))
	{
		cout << "Font not found" << endl;
	}
	title.setFont(fontTitle);
	title.setString(L"Symulacja Hodowli Robaków");
	title.setStyle(sf::Text::Bold);
	title.setCharacterSize(80);
	title.setPosition(SCRN_WIDTH / 2 - title.getGlobalBounds().width / 2, 20);

	wstring str[] = { L"Start", L"Ustawienia", L"Wyjœcie" };

	for (int i = 0; i < 3; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(65);
		text[i].setString(str[i]);
		text[i].setPosition(SCRN_WIDTH  / 2 - text[i].getGlobalBounds().width / 2, 2 * SCRN_HEIGHT / 7 + i * 120);
	}
}

void MenuScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

void MenuScreen::Update(RenderWindow &window, Event event)
{
	Vector2f mouse(sf::Mouse::getPosition(window));

	for (int i = 0; i < 3; i++)
		if (text[i].getGlobalBounds().contains(mouse))
			text[i].setFillColor(Color::Green);
		else
			text[i].setFillColor(Color::White);

	if (event.type == Event::MouseButtonReleased  && event.mouseButton.button == Mouse::Left && text[0].getGlobalBounds().contains(mouse))
	{
		ScreenManager::GetInstance().AddScreen(new RunScreen, window);
	}
	else if (event.type == Event::MouseButtonReleased  && event.mouseButton.button == Mouse::Left && text[1].getGlobalBounds().contains(mouse))
	{
		ScreenManager::GetInstance().AddScreen(new SettingsScreen, window);
	}
	else if (event.type == Event::MouseButtonReleased  && event.mouseButton.button == Mouse::Left && text[2].getGlobalBounds().contains(mouse) || event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
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
