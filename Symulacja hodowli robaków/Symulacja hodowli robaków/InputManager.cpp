#include "InputManager.h"



InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::Update(RenderWindow &window, Event event)
{
	this->event = event;
}

bool InputManager::KeyPressed(int key)
{
	if (event.key.code == key && event.type == Event::KeyPressed)
		return true;
	return false;
}

bool InputManager::KeyPressed(vector<int> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (KeyPressed(keys[i]))
			return true;
	}
	return false;
}

bool InputManager::KeyReleased(int key)
{
	if(event.key.code == key && event.type == Event::KeyReleased)
		return true;
	return false;
}

bool InputManager::KeyReleased(vector<int> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (KeyReleased(keys[i]))
			return true;
	}
	return false;
}

bool InputManager::MouseLeftPressed(int clcik)
{	
	if (event.type == Event::MouseButtonPressed  && event.mouseButton.button == clcik)
		return true;
	return false;
}

bool InputManager::MouseLeftReleased(int clcik)
{
	if (event.type == Event::MouseButtonReleased  && event.mouseButton.button == clcik)
		return true;
	return false;
}

bool InputManager::MouseLeftPressed(vector<int> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (MouseLeftPressed(keys[i]))
			return true;
	}
	return false;
}

bool InputManager::MouseLeftReleased(vector<int> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (MouseLeftReleased(keys[i]))
			return true;
	}
	return false;
}

