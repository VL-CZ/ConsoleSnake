#include "Map.h"

Map::Map(int height, int width)
{

	cells.resize(height);
	for (int i = 0; i < height; i++)
	{
		cells[i].resize(width);
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Cell empty;
			cells[i][j] = empty;
		}
	}
}

int Map::getHeight()
{
	return height;
}

int Map::getWidth()
{
	return width;
}

void Map::print()
{
}
