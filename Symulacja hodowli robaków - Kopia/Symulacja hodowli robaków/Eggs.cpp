#include "Eggs.h"



Eggs::Eggs()
{
}


Eggs::~Eggs()
{
}

void Eggs::addEgg(float x, float y)
{
	CircleShape egg;
	egg.setPosition(Vector2f(x + 21, y + 21));
	egg.setRadius(15.0f);
	egg.setOutlineThickness(3.0f);
	egg.setFillColor(Color::White);
	egg.setOutlineColor(Color(200, 200, 200));

	Egg newEgg;
	newEgg.shape = egg;
	newEgg.time = 5;
	eggs.push_back(newEgg);
}

void Eggs::draw(RenderWindow & window)
{
	for (int i = 0; i < eggs.size(); i++)
	{
		window.draw(eggs[i].shape);
	}
}
