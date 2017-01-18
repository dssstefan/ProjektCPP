#pragma once
#include "ScreenManager.h"
#include "Options.h"

class SettingsScreen : public GameScreen, public Options
{
public:
	SettingsScreen();
	~SettingsScreen();
	
	void LoadContent(RenderWindow &window);
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);
	void UpdateValue();
	void UpdateValue(int i);
private:
	Font font;
	Text plus[10];
	Text minus[10];
	Text left[9];
	Text center[10];
	Text assistant[2];
	Text returnToMenu;
	Text exit;
	vector <RectangleShape> vPlus;
	vector <RectangleShape> vMinus;
	
};

