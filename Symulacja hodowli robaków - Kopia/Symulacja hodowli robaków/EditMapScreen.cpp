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
	WIDTH = SCRN_WIDTH / TILE_SIZE + 2;
	HEIGHT = SCRN_HEIGHT / TILE_SIZE + 2;

	Sprite standard(texture[0]);
	if (MapS::GetInstace().getHeight() < HEIGHT)
		TRUEHEIGHT = MapS::GetInstace().getHeight();
	else
		TRUEHEIGHT = HEIGHT;

	sprite.resize(TRUEHEIGHT);

	if (MapS::GetInstace().getWidth() < WIDTH)
	{
		TRUEWIDTH = MapS::GetInstace().getWidth();
	}
	else
	{
		TRUEWIDTH = WIDTH;
	}

	for (int y = 0; y < TRUEHEIGHT; y++)
	{
		sprite[y].resize(TRUEWIDTH, standard);
	}

	camera = Vector2f((MapS::GetInstace().getWidth() / 2)*TILE_SIZE, (MapS::GetInstace().getHeight() / 2)*TILE_SIZE);
}


EditMapScreen::~EditMapScreen()
{
}

void EditMapScreen::LoadContent(RenderWindow & window)
{
	MapS::GetInstace().updateMap();
	updateMap();
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
			if (camera.x < 0)
				camera.x = 0;
			view.move(-TILE_SIZE, 0);
		}
		else if (event.key.code == Keyboard::Right)
		{
			camera.x += TILE_SIZE;
			if (camera.x > MapS::GetInstace().getWidth()*TILE_SIZE)
				camera.x = MapS::GetInstace().getWidth()*TILE_SIZE;
			view.move(TILE_SIZE, 0);
		}
		else if (event.key.code == Keyboard::Up)
		{
			camera.y -= TILE_SIZE;
			if (camera.y < 0)
				camera.y = 0;
			view.move(0, -TILE_SIZE);
		}
		else if (event.key.code == Keyboard::Down)
		{
			camera.y += TILE_SIZE;
			if (camera.y > MapS::GetInstace().getHeight()*TILE_SIZE)
				camera.y = MapS::GetInstace().getHeight()*TILE_SIZE;
			view.move(0, TILE_SIZE);
		}
	}
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	if (event.type == Event::MouseButtonPressed  && event.mouseButton.button == Mouse::Left)
	{
		if (window.waitEvent(event) && event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			int x = worldPos.x / TILE_SIZE;
			int y = worldPos.y / TILE_SIZE;
			MapS::GetInstace().changeTile(x, y);
		}
	}

	updateMap();
	window.setView(view);

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

void EditMapScreen::updateMap()
{
	Vector2i fixed(camera.x / TILE_SIZE, camera.y / TILE_SIZE);
	view.setCenter(fixed.x*TILE_SIZE + TILE_SIZE / 2, fixed.y*TILE_SIZE + TILE_SIZE / 2);

	Vector2f min = Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	int leftBorder = min.x / TILE_SIZE;
	int rightBorder = leftBorder + TRUEWIDTH - 2;
	
	if (min.x < 0)
	{
		int difference = abs(min.x);
		min.x += difference;
		view.move(difference, 0);

		leftBorder = min.x / TILE_SIZE;
	}
	else if (leftBorder > 0 && rightBorder - 1 <MapS::GetInstace().getWidth() - 1)
	{
		min.x -= TILE_SIZE;
		view.move(-TILE_SIZE, 0);
		leftBorder = min.x / TILE_SIZE;
	}
	else if (rightBorder - 1 >= MapS::GetInstace().getWidth() - 1)
	{
		int difference = view.getCenter().x + view.getSize().x / 2 - (MapS::GetInstace().getWidth() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.x += difference;

		leftBorder = min.x / TILE_SIZE;
		view.setCenter((leftBorder + TRUEWIDTH / 2)*TILE_SIZE + TILE_SIZE, view.getCenter().y);
	}
	else if (leftBorder == 0)
		view.move(-TILE_SIZE / 2, 0);

	int upBorder = min.y / TILE_SIZE;
	int bottomBorder = upBorder + TRUEHEIGHT - 2;

	if (min.y < 0)
	{
		int difference = abs(min.y);
		min.y += difference;
		view.move(0, difference);

		upBorder = min.y / TILE_SIZE;
	}
	else if (upBorder > 0 && bottomBorder - 1 < MapS::GetInstace().getHeight() - 1)
	{
		min.y -= TILE_SIZE;
		view.move(0, -TILE_SIZE);
		upBorder = min.y / TILE_SIZE;
	}
	else if (bottomBorder - 1 >= MapS::GetInstace().getHeight() - 1)
	{
		int difference = view.getCenter().y + view.getSize().y / 2 - (MapS::GetInstace().getHeight() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.y += difference;

		upBorder = min.y / TILE_SIZE;
		view.setCenter(view.getCenter().x, (upBorder + TRUEHEIGHT / 2)*(TILE_SIZE + 1) + TILE_SIZE);

		if (bottomBorder - 1 == MapS::GetInstace().getHeight() - 1)
			view.move(0, -TILE_SIZE / 2);
	}
	else if (upBorder == 0)
		view.move(0, -TILE_SIZE / 2);

	for (int y = 0, h = upBorder; y < TRUEHEIGHT; y++)
	{
		for (int x = 0, v = leftBorder; x < TRUEWIDTH; x++)
		{
			sprite[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
			sprite[y][x].setTexture(texture[MapS::GetInstace().tileMap[h][v].type]);
			v++;
		}
		h++;
	}
}