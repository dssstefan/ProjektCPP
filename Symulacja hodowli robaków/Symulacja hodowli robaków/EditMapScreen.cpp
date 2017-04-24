#include "EditMapScreen.h"
#include "const.h"

EditMapScreen::EditMapScreen()
{
	view.setSize(SCRN_WIDTH, SCRN_HEIGHT);
	view.setCenter(SCRN_WIDTH / 2, SCRN_HEIGHT / 2);

	for (int y = 0, i = 0; y < 4; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			texture[i].loadFromFile("data/tileset.png", IntRect(Vector2i(TILE_SIZE*x, TILE_SIZE*y), Vector2i(TILE_SIZE, TILE_SIZE)));
			i++;
		}
	}
	WIDTH = SCRN_WIDTH / TILE_SIZE;
	HEIGHT = SCRN_HEIGHT / TILE_SIZE;

	MapS::GetInstace().updateMap();

	Sprite standard(texture[0]);
	if (MapS::GetInstace().getHeight() < HEIGHT)
		TRUEHEIGHT = MapS::GetInstace().getHeight();
	else
		TRUEHEIGHT = HEIGHT;

	if (MapS::GetInstace().getWidth() < WIDTH)
	{
		TRUEWIDTH = MapS::GetInstace().getWidth();
	}
	else
	{
		TRUEWIDTH = WIDTH;
	}

	sprite.resize(MapS::GetInstace().getHeight());
	for (int y = 0; y < MapS::GetInstace().getHeight(); y++)
	{
		sprite[y].resize(MapS::GetInstace().getWidth(), standard);
	}

	for (int y = 0; y < MapS::GetInstace().getHeight(); y++)
	{
		for (int x = 0; x < MapS::GetInstace().getWidth(); x++)
		{
			sprite[y][x].setPosition(x*TILE_SIZE, y*TILE_SIZE);
			sprite[y][x].setTexture(texture[MapS::GetInstace().tileMap[y][x].type]);
		}
	}
	camera = Vector2f((MapS::GetInstace().getWidth() / 2)*TILE_SIZE, (MapS::GetInstace().getHeight() / 2)*TILE_SIZE);
}


EditMapScreen::~EditMapScreen()
{
}

void EditMapScreen::LoadContent(RenderWindow & window)
{
	window.setView(view);
}

void EditMapScreen::UnloadContent()
{
	MapS::GetInstace().updateTileC();
}

void EditMapScreen::Update(RenderWindow & window, Event event)
{
		if (event.type == Event::Closed)
			window.close();

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Left)
			{
				camera.x -= TILE_SIZE;
				if (camera.x < (TRUEWIDTH*TILE_SIZE) / 2)
				{
					camera.x = (TRUEWIDTH*TILE_SIZE) / 2;
				}
			}
			else if (event.key.code == Keyboard::Right)
			{
				camera.x += TILE_SIZE;
				if (camera.x > MapS::GetInstace().getWidth()*TILE_SIZE - (TRUEWIDTH*TILE_SIZE) / 2)
					camera.x = MapS::GetInstace().getWidth()*TILE_SIZE - (TRUEWIDTH*TILE_SIZE) / 2;
			}
			else if (event.key.code == Keyboard::Up)
			{
				camera.y -= TILE_SIZE;
				if (camera.y < (TRUEHEIGHT*TILE_SIZE) / 2)
					camera.y = (TRUEHEIGHT*TILE_SIZE) / 2;
			}
			else if (event.key.code == Keyboard::Down)
			{
				camera.y += TILE_SIZE;
				if (camera.y > MapS::GetInstace().getHeight()*TILE_SIZE - (TRUEHEIGHT*TILE_SIZE) / 2)
					camera.y = MapS::GetInstace().getHeight()*TILE_SIZE - (TRUEHEIGHT*TILE_SIZE) / 2;
			}
		}
		
		view.setCenter(camera);
		window.setView(view);

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f worldPos = window.mapPixelToCoords(pixelPos);
		if (event.type == Event::MouseButtonPressed  && event.mouseButton.button == Mouse::Left)
		{
			if (window.waitEvent(event) && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				int x = worldPos.x / TILE_SIZE;
				int y = worldPos.y / TILE_SIZE;
				MapS::GetInstace().changeTile(x, y);
				sprite[y][x].setTexture(texture[MapS::GetInstace().tileMap[y][x].type]);
			}
		}

		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			if (window.waitEvent(event) && event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
				ScreenManager::GetInstance().AddScreen(new SettingsScreen, window);

}

void EditMapScreen::Draw(RenderWindow & window)
{
	for (int y = 0; y < sprite.size(); y++)
	{
		for (int x = 0; x < sprite[y].size(); x++)
			window.draw(sprite[y][x]);
	}
}