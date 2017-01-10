#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "const.h"

class Animation
{
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;


public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();
	void Update(float deltaTime, Face face);

	sf::IntRect uvRect;
};

