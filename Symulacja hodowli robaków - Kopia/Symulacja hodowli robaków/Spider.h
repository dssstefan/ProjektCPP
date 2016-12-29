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
	void setTextureRect(sf::IntRect);
	void draw(sf::RenderWindow &);
	void setMale(bool);
	float getX();
	float getY();
	sf::Vector2u textureSize;

private:
	int hp;
	int size;
	bool isMale;

	sf::Texture *texture;
	sf::Sprite sprite;

};

