#include "SettingsScreen.h"
#include "const.h"

SettingsScreen::SettingsScreen()
{
}

SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::LoadContent(RenderWindow &window)
{
	View view;
	view.setSize(SCRN_WIDTH, SCRN_HEIGHT);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGHT / 2);
	window.setView(view);

	if (!font.loadFromFile("data/Aleo-Regular.otf"))
	{
		cout << "Font not found" << endl;
	}

	wstring str[] = { L"+" , L"-" };
	wstring lstr[] = { L"Szerokoœæ planszy", L"Wysokoœæ planszy", L"Iloœæ robaków", L"Iloœæ m³odych z jednego lêgu", L"Odpornoœæ na g³ód", L"Szybkoœæ regenerowania pod³o¿a", L"Maksymalna wielkoœæ robaka", L"Czas ¿ycia", L"Czas produktywnoœci:" };
	wstring astr[] = { L"Pocz¹tek", L"Koniec" };

	vPlus.resize(10);
	vMinus.resize(10);

	for (int i = 0; i < 10; i++)
	{
		plus[i].setFont(font);
		plus[i].setCharacterSize(40);
		plus[i].setString(str[0]);
		plus[i].setPosition(1150, 50 + 60 * i);
		vPlus[i].setPosition(1140, 55 + 60 * i);
		vPlus[i].setFillColor(Color::Black);
		vPlus[i].setSize(Vector2f(40, 40));
		vPlus[i].setOutlineThickness(3);
		vPlus[i].setOutlineColor(Color::White);

		minus[i].setFont(font);
		minus[i].setCharacterSize(40);
		minus[i].setString(str[1]);
		minus[i].setPosition(990, 50 + 60 * i);
		vMinus[i].setPosition(975, 55 + 60 * i);
		vMinus[i].setFillColor(Color::Black);
		vMinus[i].setSize(Vector2f(40, 40));
		vMinus[i].setOutlineThickness(3);
		vMinus[i].setOutlineColor(Color::White);
	}

	for (int i = 0; i < 2; i++)
	{
		assistant[i].setFont(font);
		assistant[i].setCharacterSize(40);
		assistant[i].setString(astr[i]);
		assistant[i].setPosition(650, plus[8 + i].getPosition().y);
	}

	for (int i = 0; i < 9; i++)
	{
		left[i].setFont(font);
		left[i].setCharacterSize(40);
		left[i].setString(lstr[i]);
		left[i].setPosition(100, plus[i].getPosition().y);
	}

	UpdateValue();

	for (int i = 0; i < 10; i++)
	{
		center[i].setFont(font);
		center[i].setCharacterSize(40);
		center[i].setPosition(1050, plus[i].getPosition().y);
	}
	returnToMenu.setFont(font);
	returnToMenu.setCharacterSize(60);
	returnToMenu.setString(L"Wróæ");
	returnToMenu.setPosition(100, plus[9].getPosition().y + 50);

	editMap.setFont(font);
	editMap.setCharacterSize(60);
	editMap.setString(L"Edytuj mape");
	editMap.setPosition(450, plus[9].getPosition().y + 50);

	exit.setFont(font);
	exit.setCharacterSize(60);
	exit.setString(L"WyjdŸ");
	exit.setPosition(1000, plus[9].getPosition().y + 50);
}

void SettingsScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

void SettingsScreen::Update(RenderWindow &window, Event event)
{
	Vector2f mouse(Mouse::getPosition(window));
	if (event.type == Event::MouseButtonPressed  && event.mouseButton.button == Mouse::Left)
	{
		if (window.waitEvent(event) && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			for (int i = 0; i < 10; i++)
			{
				if (vPlus[i].getGlobalBounds().contains(mouse) || plus[i].getGlobalBounds().contains(mouse))
				{
					switch (i)
					{
					case 6:
						*optionsVar[6] += 10;
						break;
					case 8:
						if (*optionsVar[8] < *optionsVar[7] && *optionsVar[8] < *optionsVar[9] )
							*optionsVar[8] += 1;
						break;
					case 9:
						if (*optionsVar[9] < *optionsVar[7] )
							*optionsVar[9] += 1;
						break;
					default:
						*optionsVar[i] += 1;
					}
					UpdateValue(i);
				}
				else if (vMinus[i].getGlobalBounds().contains(mouse))
				{
					switch (i)
					{
					case 0:
						if (*optionsVar[0] > 1)
							*optionsVar[0] -= 1;
						break;
					case 1:
						if (*optionsVar[1] > 1)
							*optionsVar[1] -= 1;
						break;
					case 6:
						if (*optionsVar[6] > 100)
							*optionsVar[6] -= 10;
						break;
					case 7:
						if (*optionsVar[7] > 1)
							*optionsVar[7] -= 1;
						if (*optionsVar[7] == *optionsVar[8] - 1)
						{
							*optionsVar[8] -= 1;
							UpdateValue(8);
						}
						if (*optionsVar[7] == *optionsVar[9] - 1)
						{
							*optionsVar[9] -= 1;
							UpdateValue(9);
						}
						break;
					case 9:
						if (*optionsVar[9] > *optionsVar[8])
							*optionsVar[9] -= 1;
						break;
					default:
						if(*optionsVar[i] > 0)
							*optionsVar[i] -= 1;
					}
					UpdateValue(i);
				}
			}
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && returnToMenu.getGlobalBounds().contains(mouse))
			{
				ScreenManager::GetInstance().AddScreen(new MenuScreen, window);
			}
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && editMap.getGlobalBounds().contains(mouse))
			{
				ScreenManager::GetInstance().AddScreen(new EditMapScreen, window);
			}
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && exit.getGlobalBounds().contains(mouse))
			{
				window.close();
			}
		}
	}
	
	if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		if(window.waitEvent(event) && event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
			ScreenManager::GetInstance().AddScreen(new MenuScreen, window);
	
	for (int i = 0; i < 10; i++)
	{
		if (mouse.y > 60 + i * 60 && mouse.y < 120 + i * 60)
		{
			if (i<9)
				left[i].setFillColor(Color::Cyan);

			minus[i].setFillColor(Color::Cyan);
			vMinus[i].setOutlineColor(Color::Cyan);
			plus[i].setFillColor(Color::Cyan);
			vPlus[i].setOutlineColor(Color::Cyan);
			center[i].setFillColor(Color::Cyan);
			if (i>7 && i <10)
				assistant[i - 8].setFillColor(Color::Cyan);
		}
		else
		{
			if (i<9)
				left[i].setFillColor(Color::White);

			minus[i].setFillColor(Color::White);
			vMinus[i].setOutlineColor(Color::White);
			plus[i].setFillColor(Color::White);
			vPlus[i].setOutlineColor(Color::White);
			center[i].setFillColor(Color::White);
			if (i>7 && i <10)
				assistant[i - 8].setFillColor(Color::White);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (vMinus[i].getGlobalBounds().contains(mouse))
		{
			minus[i].setFillColor(Color::Green);
			vMinus[i].setOutlineColor(Color::Green);
		}
		if (vPlus[i].getGlobalBounds().contains(mouse))
		{
			plus[i].setFillColor(Color::Green);
			vPlus[i].setOutlineColor(Color::Green);
		}
	}

	if (returnToMenu.getGlobalBounds().contains(mouse))
		returnToMenu.setFillColor(Color::Green);
	else
		returnToMenu.setFillColor(Color::White);

	if (editMap.getGlobalBounds().contains(mouse))
		editMap.setFillColor(Color::Green);
	else
		editMap.setFillColor(Color::White);

	if (exit.getGlobalBounds().contains(mouse))
		exit.setFillColor(Color::Green);
	else
		exit.setFillColor(Color::White);
}

void SettingsScreen::Draw(RenderWindow & window)
{
	for (int i = 0; i < 9; i++)
	{
		window.draw(left[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		window.draw(vPlus[i]);
		window.draw(vMinus[i]);
		window.draw(minus[i]);
		window.draw(plus[i]);
		window.draw(center[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		window.draw(assistant[i]);
	}
	window.draw(returnToMenu);
	window.draw(editMap);
	window.draw(exit);
}

void SettingsScreen::UpdateValue()
{
	for(int i=0; i<10;i++)
		center[i].setString(to_string(*optionsVar[i]));
}

void SettingsScreen::UpdateValue(int i)
{
	center[i].setString(to_string(*optionsVar[i]));
}
