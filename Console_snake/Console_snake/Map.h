#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
class Map
{
public:
	Map(int height, int width);

	int getHeight();
	int getWidth();

	void print();
	void placeObstacleAt(int row, int column);
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	
	void generateObstacles();
};

