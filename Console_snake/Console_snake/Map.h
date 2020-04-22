#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "MapCoordinates.h"

class Map
{
public:
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	
	Map(int height, int width, float obstacleProportion);

	int getHeight();
	int getWidth();
	int getCellCount();

	void print();
	void tryGenerateRandomValueCell();
	bool isEmpty(MapPosition position);
	std::shared_ptr<BaseCell> GetCellAtPosition(MapPosition position);
private:
	int height;
	int width;
	
	void generateObstacles(float obstacleProportion);
	bool isEmpty(int row, int column);
};

