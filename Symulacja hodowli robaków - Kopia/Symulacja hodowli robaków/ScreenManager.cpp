#include "ScreenManager.h"

GameScreen *currentScreen;
static GameScreen *previousScreen;


ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
	delete previousScreen;
	delete currentScreen;
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
	if (previousScreen != nullptr)
	{
		previousScreen->UnloadContent();
		//delete previousScreen;
	}
	//currentScreen->UnloadContent();
	previousScreen = currentScreen;
	//delete currentScreen;
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
