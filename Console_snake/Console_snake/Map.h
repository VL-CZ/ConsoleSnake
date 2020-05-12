#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "MapCoordinates.h"

class Map
{
public:
	
	Map(int height, int width, float obstacleProportion);

	int getHeight();
	int getWidth();
	int getCellCount();

	void print();
	void tryGenerateRandomValueCell();
	bool isEmpty(MapPosition position);
	std::shared_ptr<BaseCell> getCellAtPosition(MapPosition position);
	void setCellAtPosition(MapPosition position, std::shared_ptr<BaseCell> cell);
	bool tryGetValue(MapPosition position, int& value);
	std::shared_ptr<Map> getSquare(MapPosition centralPosition, int squareSize);
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	
	void generateObstacles(float obstacleProportion);
	bool isEmpty(int row, int column);
	bool isInMap(MapPosition position);
};

