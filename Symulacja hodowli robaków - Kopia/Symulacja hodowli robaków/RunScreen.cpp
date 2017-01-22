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
	window.setView(view);
}

void RunScreen::UnloadContent()
{
	GameScreen::UnloadContent();
}

void RunScreen::Update(RenderWindow & window, Event event)
{
	cout << camera.x << "  " << camera.y << "      "<< MapS::GetInstace().getWidth()*TILE_SIZE <<endl;
	if (event.type == Event::Closed)
		window.close();
	
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::Left)
		{
			camera.x -= TILE_SIZE;
			if (camera.x < (TRUEWIDTH*TILE_SIZE)/2)
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
			if (camera.y < (TRUEHEIGHT*TILE_SIZE)/2)
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