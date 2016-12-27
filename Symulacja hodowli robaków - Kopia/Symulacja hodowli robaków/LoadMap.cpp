#include "LoadMap.h"


LoadMap::LoadMap(std::string sciezka)
{
	texture.loadFromFile(sciezka);
}

LoadMap::~LoadMap()
{
}
