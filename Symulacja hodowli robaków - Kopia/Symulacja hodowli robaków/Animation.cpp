#include "Animation.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::update(float deltaTime, Face face)
{
	currentImage.y = face;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::dead(float deltaTime)
{
	currentImage.y = 4;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x + 1 > 3)
		{
			currentImage.x = 3;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::setAnimation(sf::Texture * texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	uvRect.width = int(texture->getSize().x / float(imageCount.x));
	uvRect.height = int(texture->getSize().y / float(imageCount.y));
}
