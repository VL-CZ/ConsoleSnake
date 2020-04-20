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
	int getCellCount();

	void print();
	void tryGenerateRandomValueCell();
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	
	void generateObstacles();
	bool isEmpty(int row, int column);
};

