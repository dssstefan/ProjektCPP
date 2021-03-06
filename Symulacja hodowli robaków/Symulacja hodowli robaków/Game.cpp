#include "Game.h"
#include <iostream>
#include "const.h"

Game::Game()
	:updatespider(100.0f)
{
	window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Symulacja hodowli robaków", Style::Close);
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

	WIDTH = window.getSize().x / TILE_SIZE+2;
	HEIGHT = window.getSize().y / TILE_SIZE+2;

	Sprite standard(texture[0]);

	sprite.resize(HEIGHT);
	for (int y = 0; y < HEIGHT; y++)
	{
		sprite[y].resize(WIDTH, standard);
	}

	camera = Vector2f((WIDTH/2)*TILE_SIZE, (HEIGHT/2)*TILE_SIZE);

	setMap("data/map.txt");

	createSpiders.createSpiders(spiderM, spiderF, map.getWidth(), map.getHeight());
	nourishment.generateFood(map);
}


Game::~Game()
{
}

void Game::start()
{
	Time lastUpdate = Time::Zero;
	Clock time;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left)
				{
					camera.x -= TILE_SIZE;
					view.move(-TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::Right)
				{
					camera.x += TILE_SIZE;
					view.move(TILE_SIZE, 0);
				}
				else if (event.key.code == Keyboard::Up)
				{
					camera.y -= TILE_SIZE;
					view.move(0, -TILE_SIZE);
				}
				else if (event.key.code == Keyboard::Down)
				{
					camera.y += TILE_SIZE;
					view.move(0, TILE_SIZE);
				}
				updateMap();
				window.setView(view);
			}
		}


		float deltaTime = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
		update(deltaTime);
	
		lastUpdate = time.getElapsedTime();
		draw();
	}
}

void Game::draw()
{
	window.clear();

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
			window.draw(sprite[y][x]);
	}

	nourishment.draw(window);

	for (int i = 0; i < 15; i++)
	{
		spiderM[i].draw(window);
		spiderF[i].draw(window);
	}
	
	window.display();
}

void Game::update(float deltaTime)
{
	float push = 0.0f;

	updatespider.update(spiderM, deltaTime, map);
	updatespider.update(spiderF, deltaTime, map);
	nourishment.update();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{	
			if (i == j) {
				continue;
			}
			spiderM[i].getCollider().CheckCollision(spiderM[j].getCollider(), 0.0f);
			spiderM[i].getCollider().CheckCollision(spiderF[j].getCollider(), 0.0f);

			int eat = nourishment.isEating(spiderM[i], 30.0f);
			for (int k = 1; k <= eat; k++)
			{
				//JEDZENIE
			}
			
		}

		for (int j = 0; j < 15; j++)
		{
			if (i == j) {
				continue;
			}
			spiderF[i].getCollider().CheckCollision(spiderM[j].getCollider(), 0.0f);
			spiderF[i].getCollider().CheckCollision(spiderF[j].getCollider(), 0.0f);

			int eat = nourishment.isEating(spiderF[i], 30.0f);
			for (int k = 1; k <= eat; k++)
			{
				//JEDZENIE
			}
		}

		for (int j = 0; j < map.tileC.size(); j++)
		{
			spiderM[i].getCollider().CheckCollision(map.getCollider(map.tileC[j]), 0.0f);
			spiderF[i].getCollider().CheckCollision(map.getCollider(map.tileC[j]), 0.0f);
		}
		
	}
}

void Game::setMap(string name)
{
	if (!map.loadFromFile())
	{
		cout << "Problem z załadowaniem mapy!";
		return;
	}

	updateMap();
	window.setView(view);
}

void Game::updateMap()
{
	Vector2i fixed(camera.x / TILE_SIZE, camera.y / TILE_SIZE);
	view.setCenter(fixed.x*TILE_SIZE + TILE_SIZE / 2, fixed.y*TILE_SIZE + TILE_SIZE / 2);

	Vector2f min = Vector2f(view.getCenter().x - view.getSize().x / 2, view.getCenter().y - view.getSize().y / 2);
	int leftBorder = min.x / TILE_SIZE;
	int rightBorder = leftBorder + WIDTH - 2;

	if (min.x < 0)
	{
		int difference = abs(min.x);
		min.x += difference;
		view.move(difference, 0);

		leftBorder = min.x / TILE_SIZE;
	}
	else if (leftBorder > 0 && rightBorder - 1 < map.getWidth() - 1)
	{
		min.x -= TILE_SIZE;
		view.move(-TILE_SIZE, 0);
		leftBorder = min.x / TILE_SIZE;
	}
	else if (rightBorder - 1 >= map.getWidth() - 1)
	{
		int difference = view.getCenter().x + view.getSize().x / 2 - (map.getWidth() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.x += difference;

		leftBorder = min.x / TILE_SIZE;
		view.setCenter((leftBorder + WIDTH / 2)*TILE_SIZE + TILE_SIZE, view.getCenter().y);
	}
	else if (leftBorder == 0)
		view.move(-TILE_SIZE / 2, 0);

	int upBorder = min.y / TILE_SIZE;
	int bottomBorder = upBorder + HEIGHT - 2;

	if (min.y < 0)
	{
		int difference = abs(min.y);
		min.y += difference;
		view.move(0, difference);

		upBorder = min.y / TILE_SIZE;
	}
	else if (upBorder > 0 && bottomBorder - 1 < map.getHeight() - 1)
	{
		min.y -= TILE_SIZE;
		view.move(0,-TILE_SIZE);
		upBorder = min.y / TILE_SIZE;
	}
	else if (bottomBorder - 1 >= map.getHeight() - 1)
	{
		int difference = view.getCenter().y + view.getSize().y / 2 - (map.getHeight() - 1)*TILE_SIZE;

		difference = -difference - TILE_SIZE;
		min.y += difference;

		upBorder = min.y / TILE_SIZE;
		view.setCenter(view.getCenter().x ,(upBorder + HEIGHT / 2)*TILE_SIZE + TILE_SIZE);

		if (bottomBorder - 1 == map.getHeight() - 1)		
			view.move(0, -TILE_SIZE / 2);
	}
	else if (upBorder == 0)
		view.move(0, -TILE_SIZE /2);

	for (int y = 0, h = upBorder; y < HEIGHT; y++)
	{
		for (int x = 0, v = leftBorder; x < WIDTH; x++)
		{
			sprite[y][x].setPosition(v*TILE_SIZE, h*TILE_SIZE);
			sprite[y][x].setTexture(texture[map.tileMap[h][v].type]);
			v++;
		}
		h++;
	}
}
