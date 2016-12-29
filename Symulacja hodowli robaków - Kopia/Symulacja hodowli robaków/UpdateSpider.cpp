#include "UpdateSpider.h"
#include <iostream>


UpdateSpider::UpdateSpider(float speed)
{
	this->speed = speed;
	movement.x = 0.0f;
	movement.y = 0.0f;
	position = DOWN;
}


UpdateSpider::~UpdateSpider()
{
}

void UpdateSpider::update(vector <Spider> &spider, float deltaTime)
{
	movement.x = 0.0f;
	movement.y = 0.0f;
	/*srand(time(NULL));

	switch (rand() % 4 + 1)
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

	spider.move(movement.x, movement.y);
*/
	for (int i = 0; i < 15; i++)
	{
		int r = rand() % 4 + 1;
		switch (r)
		{
		case 1:
			movement.x -= speed *deltaTime + 1;
			break;
		case 2:
			movement.y -= speed *deltaTime + 1;
			break;
		case 3:
			movement.x += speed *deltaTime + 1;
			break;
		case 4:
			movement.y += speed *deltaTime + 1;
			break;
		default:
			break;
		}

		spider[i].move(movement.x, movement.y);

	}

}