#include "ScreenManager.h"

GameScreen *currentScreen, *newScreen, *previousScreen;


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

void ScreenManager::LoadContent(RenderWindow &window)
{
	currentScreen->LoadContent(window);
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

void ScreenManager::AddScreen(GameScreen * screen, RenderWindow &window)
{
	previousScreen = currentScreen;
	currentScreen->UnloadContent();
	delete currentScreen;
	currentScreen = screen;
	currentScreen->LoadContent(window);
}

void ScreenManager::ChangeScreen( RenderWindow &window)
{
	currentScreen->UnloadContent();
	delete currentScreen;
	currentScreen = previousScreen;
	currentScreen->LoadContent(window);
}
