#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "const.h"

class Animation
{
public:
	Animation();
	~Animation();
	void update(float deltaTime, Face face);
	void setAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	sf::IntRect uvRect;

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
};

