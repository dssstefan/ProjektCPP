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
	
	moveSpider(spider, deltaTime, map);

}

void UpdateSpider::moveSpider(vector<Spider>& spider, float deltaTime, Map map)
{

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(1, 4);
	std::uniform_int_distribution<int> distribution2(1, 200);
	int random = 0;
	for (int i = 0; i < 15; i++)
	{
		movement.x = 0.0f;
		movement.y = 0.0f;

		if (spider[i].count == 0)
		{

			random = distribution(generator);
			spider[i].random = random;

			random = distribution2(generator);
			spider[i].count = random;
			
		}
		else
			spider[i].count--;

		switch (spider[i].random)
		{
		case 1:
			movement.x -= speed *deltaTime;
			break;
		case 2:
			movement.y -= speed *deltaTime;
			break;
		case 3:
			movement.x += speed *deltaTime;
			break;
		case 4:
			movement.y += speed *deltaTime;
			break;
		default:
			break;
		}
		spider[i].addMovement(movement.x, movement.y);
		checkBorderCollision(spider[i], map);

		movement = spider[i].getMovement();
		spider[i].move(movement.x, movement.y, deltaTime, checkFace(movement));
	

	}

}

void UpdateSpider::checkBorderCollision(Spider& spider, Map map)
{
	Vector2f movement = spider.getMovement();
	Vector2f nextPos(spider.getX() + movement.x, spider.getY() + movement.y);

	if (nextPos.x <= 0.0f)
	{
		spider.setMovement(-movement.x, movement.y);
	}
	else if (nextPos.x >= map.getWidth()*TILE_SIZE - 64)
	{
		spider.setMovement(-movement.x, movement.y);
	}
	else if (nextPos.y <= 0.0f)
	{
		spider.setMovement(movement.x, -movement.y);
	}
	else if (nextPos.y >= map.getHeight()*TILE_SIZE -64)
	{
		spider.setMovement(movement.x, -movement.y);
	}



}

Face UpdateSpider::checkFace(Vector2f movement)
{
	if (movement.y >= movement.x && movement.y >= -movement.x)
		return UP;

	if (movement.y > movement.x && movement.y < -movement.x)
		return LEFT;

	if (movement.y <= movement.x && movement.y <= -movement.x)
		return DOWN;

	if (movement.y < movement.x && movement.y > -movement.x)
		return RIGHT;
}
