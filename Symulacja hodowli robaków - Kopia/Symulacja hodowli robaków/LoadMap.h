#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class LoadMap
{
	sf::Texture texture;

public:
	LoadMap(std::string sciezka);
	~LoadMap();
};

