#include "UpdateSpider.h"
#include <iostream>
#include <random>

UpdateSpider::UpdateSpider(float speed)
{
	this->speed = speed;
	movement.x = 0.0f;
	movement.y = 0.0f;
	face = DOWN;
	lastUpdate = Time::Zero;
	delta = 0.0f;

}


UpdateSpider::~UpdateSpider()
{
}

void UpdateSpider::update(vector <Spider> &spider, vector <Spider> &deadSpider, float deltaTime)
{
	time.restart();
	moveSpider(spider, deltaTime);
	deltaTime += time.getElapsedTime().asSeconds();
	for (int i = 0; i < spider.size(); i++)
	{
		spider[i].lifeTime -= deltaTime;
		spider[i].hp -= deltaTime;
		if(spider[i].lifeTime <= 0 || spider[i].hp <= 0)
		{
			deadSpider.push_back(spider[i]);
			spider[i] = spider[spider.size() - 1];
			spider.pop_back();
		}
		else
		{
			spider[i].minProductiveTime -= deltaTime;
			spider[i].maxProductiveTime -= deltaTime;
		}
	}

	for (int i = 0; i < deadSpider.size(); i++)
	{
		deadSpider[i].lifeTime -= deltaTime;
		deadSpider[i].death(deltaTime);

		if (deadSpider[i].lifeTime <= -5)
		{
			deadSpider[i] = deadSpider[deadSpider.size() - 1];
			deadSpider.pop_back();
		}
	}
}

void UpdateSpider::moveSpider(vector<Spider>& spider, float deltaTime)
{

	random_device generator;
	uniform_int_distribution<int> distribution(1, 4);
	uniform_int_distribution<int> distribution2(1, 50);
	int random = 0;

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
		checkBorderCollision(spider[i]);

		movement = spider[i].getMovement();
		spider[i].move(movement.x, movement.y, deltaTime, checkFace(movement));
	}
}

void UpdateSpider::checkBorderCollision(Spider& spider)
{
	Vector2f movement = spider.getMovement();
	Vector2f nextPos(spider.getX() + movement.x, spider.getY() + movement.y);

	if (nextPos.x <= 0.0f)
	{
		spider.setPosition(0, spider.getY());
		spider.setMovement(-movement.x, movement.y);
	}
	if (nextPos.x >= MapS::GetInstace().getWidth()*TILE_SIZE - 64)
	{
		spider.setPosition(MapS::GetInstace().getWidth()*TILE_SIZE - 64, spider.getY());
		spider.setMovement(-movement.x, movement.y);
	}
	if (nextPos.y <= 0.0f)
	{
		spider.setPosition(spider.getX(), 0);
		spider.setMovement(movement.x, -movement.y);
	}
	if (nextPos.y >= MapS::GetInstace().getHeight()*TILE_SIZE -64)
	{
		spider.setPosition(spider.getX(), MapS::GetInstace().getHeight()*TILE_SIZE - 64);
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
