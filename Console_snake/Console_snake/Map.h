#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "Snake.h"

class Map
{
public:
	Map(int height, int width, std::vector<std::shared_ptr<BaseSnake>> snakes);

	int getHeight();
	int getWidth();
	int getCellCount();

	void print();
	void tryGenerateRandomValueCell();
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	std::vector<std::shared_ptr<BaseSnake>> snakes;
	
	void generateObstacles();
	void printSummary();
	bool isEmpty(int row, int column);
};

