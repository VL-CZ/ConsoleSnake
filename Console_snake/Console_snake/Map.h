#pragma once
#include <vector>
#include "Cell.h"
class Map
{
public:
	Map(int height, int width);

	int getHeight();
	int getWidth();

	void print();
private:
	int height;
	int width;
	std::vector<std::vector<Cell>> cells;
};

