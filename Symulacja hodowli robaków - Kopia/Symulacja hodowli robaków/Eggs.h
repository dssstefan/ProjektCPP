#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Eggs
{
public:
	Eggs();
	~Eggs();

	void addEgg(float x, float y);
	void draw(RenderWindow &window);

	struct Egg {
		CircleShape shape;
		float time;
	};

	vector<Egg> eggs;
};