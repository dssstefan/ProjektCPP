#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;


class InputManager
{
public:
	InputManager();
	~InputManager();

	void Update(RenderWindow &window, Event event);
	bool KeyPressed(int key);
	bool KeyPressed(vector<int> keys);
	
	bool KeyReleased(int key);
	bool KeyReleased(vector<int> keys);

	bool MouseLeftPressed(int clcik);
	bool MouseLeftReleased(int click);
	bool MouseLeftPressed(vector<int> keys);
	bool MouseLeftReleased(vector<int> keys);
private:
	Event event;
};

