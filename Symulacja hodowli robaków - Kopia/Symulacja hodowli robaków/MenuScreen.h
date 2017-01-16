#pragma once
#include "ScreenManager.h"

class MenuScreen : public GameScreen
{
public:
	MenuScreen();
	~MenuScreen();

	void LoadContent();
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);
private:
	Font font;
	Text title;
	Text text[3];
	int click;
};

