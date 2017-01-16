#include "SettingsScreen.h"
#include "const.h"


SettingsScreen::SettingsScreen()
{
}


SettingsScreen::~SettingsScreen()
{
}

void SettingsScreen::LoadContent()
{
	if (!font.loadFromFile("data/AmaticSC-Regular.ttf"))
	{
		cout << "Font not found" << endl;
	}

	string str[] = { "+" , "-" };
	string lstr[] = { "Szerokoœæ planszy", "Wysokoœæ planszy", "Iloœæ robaków", "Iloœæ m³odych z jednego lêgu", "Odpornoœæ na g³ód", "Szybkoœæ regenerowania pod³o¿a", "Maksymalna wielkoœæ robaka", "Czas ¿ycia", "Czas produktywnoœci:" };
	string astr[] = { "Pocz¹tek", "Koniec" };

	vPlus.resize(10);
	vMinus.resize(10);

	for (int i = 0; i < 10; i++)
	{
		plus[i].setFont(font);
		plus[i].setCharacterSize(40);
		plus[i].setString(str[0]);
		plus[i].setPosition(1150, 60 + 60 * i);
		vPlus[i].setPosition(1140, 65 + 60 * i);
		vPlus[i].setFillColor(Color::Black);
		vPlus[i].setSize(Vector2f(40, 40));
		vPlus[i].setOutlineThickness(3);
		vPlus[i].setOutlineColor(Color::White);

		minus[i].setFont(font);
		minus[i].setCharacterSize(40);
		minus[i].setString(str[1]);
		minus[i].setPosition(990, 60 + 60 * i);
		vMinus[i].setPosition(975, 65 + 60 * i);
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
		assistant[i].setPosition(450, plus[8 + i].getPosition().y);
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
	returnToMenu.setString("Wróæ");
	returnToMenu.setPosition(100, plus[9].getPosition().y + 40);

	click = Mouse::Left;
	key = Keyboard::Return;
}

void SettingsScreen::UnloadContent()
{
	GameScreen::UnloadContent();
	click = NULL;
}

void SettingsScreen::Update(RenderWindow &window, Event event)
{
	input.Update(window, event);

	Vector2f mouse(Mouse::getPosition(window));

	
	
	while (window.pollEvent(event))
	{
		if (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left)
		{
			
			for (int i = 0; i < 10; i++)
			{
				if (vPlus[i].getGlobalBounds().contains(mouse))
				{
					if (i == 6)
						*value[i] += 10;
					else
						*value[i] += 1;
					UpdateValue(i);
					break;
				}
				else if (vMinus[i].getGlobalBounds().contains(mouse))
				{
					if (*value[i] > 0)
					{
						if (i == 6)
							*value[i] -= 10;
						else
							*value[i] -= 1;
						UpdateValue(i);
					}
				}
			}
		}
	}

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

	if (input.MouseLeftReleased(click) && returnToMenu.getGlobalBounds().contains(mouse))
	{
		ScreenManager::GetInstance().AddScreen(new MenuScreen);
	}

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
}

void SettingsScreen::UpdateValue()
{
	string cstr[] = { to_string(boardWidth), to_string(boardHeight), to_string(spiderQuantity), to_string(bornSpiderQuantity), to_string(health), to_string(foodRegeneration), to_string(maxSize) + " %", to_string(lifeTime), to_string(minProductiveTime), to_string(maxProductiveTime) };
	for(int i=0; i<10;i++)
		center[i].setString(cstr[i]);
}

void SettingsScreen::UpdateValue(int i)
{
	center[i].setString(to_string(*value[i]));
}
