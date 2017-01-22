#pragma once
#include "ScreenManager.h"
#include "MapS.h"

class EditMapScreen : public GameScreen
{
public:
	EditMapScreen();
	~EditMapScreen();

	void LoadContent(RenderWindow &window);
	void UnloadContent();
	void Update(RenderWindow &window, Event event);
	void Draw(RenderWindow &window);
private:
	View view;
	int WIDTH;
	int HEIGHT;
	int TRUEWIDTH;
	int TRUEHEIGHT;
	Texture texture[12];
	vector<vector<Sprite>> sprite;
	Vector2f camera;
};