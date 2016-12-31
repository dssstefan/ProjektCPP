#pragma once
#include <SFML\Graphics.hpp>

class Spider
{
public:
	Spider();
	~Spider();

	void move(float x, float y);
	void setPosition(float x, float y);
	void setTexture(sf::Texture &t);
	void setTextureRect(sf::IntRect);
	void addMovement(float x, float y);
	void setMovement(float x, float y);
	sf::Vector2f getMovement();
	void draw(sf::RenderWindow &);
	void setMale(bool);
	float getX();
	float getY();
	sf::Vector2u textureSize;
	int count;
	int random;
private:
	int hp;
	int size;
	bool isMale;
	sf::Vector2f movement;

	sf::Texture *texture;
	sf::Sprite sprite;

};

