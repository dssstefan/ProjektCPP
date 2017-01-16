#include "ScreenManager.h"

GameScreen *currentScreen, *newScreen;

ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
}

ScreenManager & ScreenManager::GetInstance()
{
	static ScreenManager instance;
	return instance;
}

void ScreenManager::Initialize()
{
	currentScreen = new MenuScreen();
}

void ScreenManager::LoadContent()
{
	currentScreen->LoadContent();
}

void ScreenManager::UnloadContent()
{

}

void ScreenManager::Update(RenderWindow &window, Event event)
{
	currentScreen->Update(window, event);
}

void ScreenManager::Draw(RenderWindow & window)
{
	currentScreen->Draw(window);
}

void ScreenManager::AddScreen(GameScreen * screen)
{
	currentScreen->UnloadContent();
	delete currentScreen;
	currentScreen = screen;
	currentScreen->LoadContent();
}
