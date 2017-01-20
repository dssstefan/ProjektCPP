#include "UpdateSpider.h"
#include <iostream>
#include <random>

UpdateSpider::UpdateSpider(float speed)
{
	this->speed = speed;
	movement.x = 0.0f;
	movement.y = 0.0f;
	face = DOWN;
}


UpdateSpider::~UpdateSpider()
{
}

void UpdateSpider::update(vector <Spider> &spider, float deltaTime, Map map)
{
	
	moveSpider(spider, map);

}

void UpdateSpider::moveSpider(vector<Spider>& spider, Map map)
{

	random_device generator;
	uniform_int_distribution<int> distribution(1, 4);
	uniform_int_distribution<int> distribution2(1, 50);
	int random = 0;
	float deltaTime = time.getElapsedTime().asSeconds() - lastUpdate.asSeconds();
	for (int i = 0; i < spider.size(); i++)
	{
		movement.x = 0.0f;
		movement.y = 0.0f;

		if (spider[i].wait == 0)
		{

			random = distribution(generator);
			spider[i].random = random;

			random = distribution2(generator);
			spider[i].wait = random;
			
		}
		else
			spider[i].wait--;

		switch (spider[i].random)
		{
		case 1:
			movement.x -= speed * deltaTime;
			break;
		case 2:
			movement.y -= speed * deltaTime;
			break;
		case 3:
			movement.x += speed * deltaTime;
			break;
		case 4:
			movement.y += speed * deltaTime;
			break;
		default:
			break;
		}
		spider[i].addMovement(movement.x, movement.y);
		checkBorderCollision(spider[i], map);

		movement = spider[i].getMovement();
		spider[i].move(movement.x, movement.y, deltaTime, checkFace(movement));
	

	}
	lastUpdate = time.getElapsedTime();
}

void UpdateSpider::checkBorderCollision(Spider& spider, Map map)
{
	Vector2f movement = spider.getMovement();
	Vector2f nextPos(spider.getX() + movement.x, spider.getY() + movement.y);

	if (nextPos.x <= 0.0f)
	{
		spider.setPosition(0, spider.getY());
		spider.setMovement(-movement.x, movement.y);
	}
	if (nextPos.x >= map.getWidth()*TILE_SIZE - 64)
	{
		spider.setPosition(map.getWidth()*TILE_SIZE - 64, spider.getY());
		spider.setMovement(-movement.x, movement.y);
	}
	if (nextPos.y <= 0.0f)
	{
		spider.setPosition(spider.getX(), 0);
		spider.setMovement(movement.x, -movement.y);
	}
	if (nextPos.y >= map.getHeight()*TILE_SIZE -64)
	{
		spider.setPosition(spider.getX(), map.getHeight()*TILE_SIZE - 64);
		spider.setMovement(movement.x, -movement.y);
	}



}

Face UpdateSpider::checkFace(Vector2f movement)
{
	if (movement.y >= movement.x && movement.y >= -movement.x)
		return UP;

	if (movement.y >= movement.x && movement.y <= -movement.x)
		return LEFT;

	if (movement.y <= movement.x && movement.y <= -movement.x)
		return DOWN;

	if (movement.y <= movement.x && movement.y >= -movement.x)
		return RIGHT;

	return DOWN;
}
