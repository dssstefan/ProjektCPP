#pragma once
#include <iostream>
#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingsScreen.h"
#include "RunScreen.h"
#include "PauseScreen.h"

class ScreenManager
{
public:
	~ScreenManager();
	static ScreenManager &GetInstance();

	void Initialize();
	void LoadContent(RenderWindow &window);
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);

	void AddScreen(GameScreen *screen, RenderWindow &window);
	void ChangeScreen( RenderWindow &window);
protected:
	
private:

	ScreenManager();
	ScreenManager(ScreenManager const&);
};

