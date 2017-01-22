#include "RunScreen.h"

RunScreen::RunScreen() :updatespider(100.0f)
{
	push = 0.0f;
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

	MapS::GetInstace().updateMap();

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
	view.setViewport(getViewPort());
	camera = Vector2f((MapS::GetInstace().getWidth() / 2)*TILE_SIZE, (MapS::GetInstace().getHeight() / 2)*TILE_SIZE);
	createSpiders.createSpiders(spiderM, spiderF, MapS::GetInstace().getWidth()-1, MapS::GetInstace().getHeight()-1);
	nourishment.generateFood();
}


RunScreen::~RunScreen()
{
}

void RunScreen::LoadContent(RenderWindow &window)
{
	time.restart();
	lastUpdate = Time::Zero;

	for (int i = 0; i < spiderM.size(); i++)
	{
		spiderM[i].updateOptions();
	}

	for (int i = 0; i < spiderF.size(); i++)
	{
		spiderF[i].updateOptions();
	}
	updateMap();
	window.setView(view);
}

void RunScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

void RunScreen::Update(RenderWindow & window, Event event)
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

	updateMap();
	window.setView(view);

	float deltaTime = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
	updatespider.update(spiderM, deadSpider, deltaTime);
	updatespider.update(spiderF, deadSpider, deltaTime);

	deltaTime = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
	nourishment.update(deltaTime);

	deltaTime = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
	for (int i = 0; i < spiderInPregnacy.size(); i++)
	{
		spiderInPregnacy[i]->pregnacyTime -= deltaTime;
		
		if (spiderInPregnacy[i]->pregnacyTime <= 0)
		{
			spiderInPregnacy[i]->pregnacyTime = 5;
			spiderInPregnacy[i] = spiderInPregnacy[spiderInPregnacy.size() - 1];
			spiderInPregnacy.pop_back();
			i--;
		}
	}

	for (int i = 0; i < eggs.eggs.size(); i++)
	{
		eggs.eggs[i].time -= deltaTime;
		if (eggs.eggs[i].time <= 0)
		{
			createSpiders.addSpiders(spiderM, spiderF, eggs.eggs[i].shape.getPosition(), *optionsVar[3]);
			eggs.eggs[i] = eggs.eggs[eggs.eggs.size() - 1];
			eggs.eggs.pop_back();
			i--;
		}
	}
	lastUpdate = time.getElapsedTime();
	
	for (int i = 0; i < spiderM.size(); i++)
	{
		for (int j = 0; j < spiderM.size(); j++)
		{
			if (i == j) {
				continue;
			}
			spiderM[i].getCollider().CheckCollision(spiderM[j].getCollider(), 0.0f);
		}
		/*for (int j = 0; j < spiderF.size(); j++)
		{
			spiderM[i].getCollider().CheckCollision(spiderF[j].getCollider(), 0.0f);
		}*/
		int eat = nourishment.isEating(spiderM[i], *optionsVar[5]);
		if (eat > 0)
		{
			spiderM[i].hp = *optionsVar[4];
			spiderM[i].grow(eat);
		}
		for (int j = 0; j < MapS::GetInstace().tileC.size(); j++)
		{
			if (spiderM[i].getCollider().CheckCollision(MapS::GetInstace().getCollider(MapS::GetInstace().tileC[j]), 0.0f))
				spiderM[i].setMovement(-spiderM[i].getMovement().x, -spiderM[i].getMovement().y);
		}
	}

	for (int i = 0; i < spiderF.size(); i++)
	{
		for (int j = 0; j < spiderF.size(); j++)
		{
			if (i == j) {
				continue;
			}
			spiderF[i].getCollider().CheckCollision(spiderF[j].getCollider(), 0.0f);
		}
		for (int j = 0; j < spiderM.size(); j++)
		{
			if(spiderF[i].getCollider().CheckCollision(spiderM[j].getCollider(), 0.0f))
			{
				if (spiderF[i].pregnacyTime >= 5 && spiderF[i].minProductiveTime <= 0 && spiderF[i].maxProductiveTime >= 0 && spiderM[j].minProductiveTime <= 0 && spiderM[j].maxProductiveTime >= 0)
				{
					spiderF[i].pregnacyTime -= 0.01;
					spiderInPregnacy.push_back(&spiderF[i]);
					eggs.addEgg(spiderF[i].getX(), spiderF[i].getY());
				}
			}
		}
		int eat = nourishment.isEating(spiderF[i], *optionsVar[5]);
		if (eat > 0)
		{
			spiderF[i].hp = *optionsVar[4];
			spiderF[i].grow(eat);
		}
		for (int j = 0; j < MapS::GetInstace().tileC.size(); j++)
		{
			if (spiderF[i].getCollider().CheckCollision(MapS::GetInstace().getCollider(MapS::GetInstace().tileC[j]), 0.0f))
				spiderF[i].setMovement(-spiderF[i].getMovement().x, -spiderF[i].getMovement().y);
		}
	}

	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
		if (window.waitEvent(event) && event.type == Event::KeyReleased && event.key.code == Keyboard::Escape)
			ScreenManager::GetInstance().AddScreen(new PauseScreen, window);
}

void RunScreen::updateMap()
{
	Vector2i fixed(camera.x / TILE_SIZE, camera.y / TILE_SIZE);
	view.setCenter(fixed.x*TILE_SIZE + TILE_SIZE / 2, fixed.y*TILE_SIZE + TILE_SIZE / 2);

	Vector2f min = Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	int leftBorder = min.x / TILE_SIZE;
	int rightBorder = leftBorder + TRUEWIDTH - 2;

	if (min.x < 0)
	{
		float difference = abs(min.x);
		min.x += difference;
		view.move(difference, 0);

		leftBorder = min.x / TILE_SIZE;
	}
	else if (leftBorder > 0 && rightBorder - 1 < MapS::GetInstace().getWidth() - 1)
	{
		min.x -= TILE_SIZE;
		view.move(-TILE_SIZE, 0);
		leftBorder = min.x / TILE_SIZE;
	}
	else if (rightBorder - 1 >= MapS::GetInstace().getWidth() - 1)
	{
		float difference = view.getCenter().x + view.getSize().x / 2 - (MapS::GetInstace().getWidth() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.x += difference;

		leftBorder = (min.x) / TILE_SIZE;
		view.setCenter((leftBorder + (TRUEWIDTH) / 2)*TILE_SIZE + TILE_SIZE, view.getCenter().y);
	}
	else if (leftBorder == 0)
	{
		view.move(-TILE_SIZE / 2, 0);
	}

	int upBorder = min.y / TILE_SIZE;
	int bottomBorder = upBorder + TRUEHEIGHT - 2;

	if (min.y < 0)
	{
		float difference = abs(min.y);
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
	else if (bottomBorder - 1  >= MapS::GetInstace().getHeight() - 1)
	{
		float difference = view.getCenter().y + view.getSize().y / 2 - (MapS::GetInstace().getHeight() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.y += difference;

		upBorder = (min.y) / TILE_SIZE;
		view.setCenter(view.getCenter().x, (upBorder + (TRUEHEIGHT) / 2)*TILE_SIZE + TILE_SIZE);

		if (bottomBorder -1  == MapS::GetInstace().getHeight() -1 )
			view.move(0, -TILE_SIZE / 2);
	}
	else if (upBorder == 0)
	{
		view.move(0, -TILE_SIZE / 2);
	}

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

FloatRect RunScreen::getViewPort()
{
	if (TRUEHEIGHT < HEIGHT - 2 && TRUEWIDTH >= WIDTH - 2)
	{
		return FloatRect(0.0f, (1- (float)TRUEHEIGHT/((float)HEIGHT-2))/2, 1.0f, 1.0f);
	}
	if (TRUEHEIGHT >= HEIGHT - 2 && TRUEWIDTH < WIDTH - 2)
	{
		return FloatRect((1 - (float)TRUEWIDTH / ((float)WIDTH - 2)) / 2, 0.0f, 1.0f, 1.0f);
	}
	if (TRUEHEIGHT < HEIGHT - 2 && TRUEWIDTH < WIDTH - 2)
	{
		return FloatRect((1 - (float)TRUEWIDTH / ((float)WIDTH - 2)) / 2, (1 - (float)TRUEHEIGHT / ((float)HEIGHT - 2)) / 2, 1.0f, 1.0f);
	}
	return FloatRect(0.0f, 0.0f, 1.0f, 1.0f);
}

void RunScreen::Draw(RenderWindow & window)
{
	for (int y = 0; y < sprite.size(); y++)
	{
		for (int x = 0; x < sprite[y].size(); x++)
			window.draw(sprite[y][x]);
	}

	nourishment.draw(window);

	for (int i = 0; i < deadSpider.size(); i++)
	{
		deadSpider[i].draw(window);
	}

	eggs.draw(window);

	for (int i = 0; i < spiderF.size(); i++)
	{
		spiderF[i].draw(window);
	}

	for (int i = 0; i < spiderM.size(); i++)
	{
		spiderM[i].draw(window);
	}
}