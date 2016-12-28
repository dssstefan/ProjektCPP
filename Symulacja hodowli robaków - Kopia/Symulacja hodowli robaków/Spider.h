#pragma once
#include <SFML\Graphics.hpp>

class Spider
{
public:
	Spider();
	~Spider();

	void move(int x, int y);
	void setPosition(int x, int y);
	void setTexture(sf::Texture &);
	void draw(sf::RenderWindow &);
	float getX();
	float getY();

protected:
	int hp;
	int size;

	sf::Texture *texture;
	sf::Sprite sprite;
};

