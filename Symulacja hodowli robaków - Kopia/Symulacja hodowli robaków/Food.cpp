#include "Food.h"
#include <random>


Food::Food()
{
}


Food::~Food()
{
}

void Food::generateFood(Map &map)
{
	random_device generator;
	uniform_int_distribution<int> distribution(0, 255);
	Circle newFood;
	
	foods.resize(map.getWidth());

	for (int i = 0; i < map.getHeight(); i++)
	{
		foods[i].resize(map.getWidth());
	}

	for (int y = 0; y < map.getHeight(); y++)
	{
		for (int x = 0; x < map.getWidth(); x++)
		{
			if (map.tileMap[y][x].interactable)
			{
				newFood.shape.setPosition(x * TILE_SIZE + TILE_SIZE / 2 - 8, y * TILE_SIZE + TILE_SIZE / 2 - 8);
				newFood.shape.setRadius(5.0f);
				newFood.shape.setOutlineThickness(3.0f);
				newFood.shape.setFillColor(Color(distribution(generator), distribution(generator), distribution(generator)));
				newFood.shape.setOutlineColor(Color(distribution(generator), distribution(generator), distribution(generator)));
				newFood.active = true;

				foods[y][x] = newFood;
			}
			else
			{
				newFood.shape.setPosition(x * TILE_SIZE + TILE_SIZE / 2 - 8, y * TILE_SIZE + TILE_SIZE / 2 - 8);
				newFood.shape.setRadius(1.0f);
				newFood.shape.setFillColor(Color::Black);
				newFood.active = false;
			}
		}
	}
}

void Food::draw(RenderWindow &window)
{
	for (int i = 0; i < foods.size(); i++)
	{
		for (int j = 0; j < foods[i].size(); j++)
		{
			if (foods[i][j].active)
				window.draw(foods[i][j].shape);
		}
	}
}

void Food::eaten(int i, int j, int cooldown)
{
	foods[i][j].active = false;
	foods[i][j].cooldownInSec = cooldown;
	foodsInCd.push_back(&foods[i][j]);
}

void Food::update(float *deltaTime)
{
	if (foodsInCd.size())
	{
		for (int i = 0; i < foodsInCd.size(); i++)
		{
			foodsInCd[i]->cooldownInSec -= *deltaTime;

			if (foodsInCd[i]->cooldownInSec < 0)
			{
				foodsInCd[i] = foodsInCd[foodsInCd.size() - 1];
				foodsInCd.pop_back();
				i--;
			}

		}

	}

}

int Food::isEating(Spider spider, float cooldown)
{
	Vector2f corner(spider.getX(), spider.getY());
	Vector2f size(spider.getGlobalBounds().width, spider.getGlobalBounds().height);

	int eat = 0;

	int jmin = (int)corner.x / TILE_SIZE;
	int jmax = (int)corner.x / TILE_SIZE + size.x / TILE_SIZE;
	int imin = (int)corner.y / TILE_SIZE;
	int imax = (int)corner.y / TILE_SIZE + size.y / TILE_SIZE;

	for (int i = imin; i <= imax && i < foods.size() ; i++)
	{
		for (int j = jmin; j <= jmax && j < foods[i].size(); j++)
		{
			if (spider.getGlobalBounds().intersects(foods[i][j].shape.getGlobalBounds()))
			{
				eaten(i, j, cooldown);
				eat++;
			}
		}
	}

	return eat;
}
