#pragma once
#include "ScreenManager.h"

class MenuScreen : public GameScreen
{
public:
	MenuScreen();
	~MenuScreen();

	void LoadContent(RenderWindow &window);
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);
private:
	Font font;
	Font fontTitle;
	Text title;
	Text text[3];
};

