#include "Map.h"
using namespace std;

Map::Map(int height, int width)
{
	this->height = height;
	this->width = width;

	for (int i = 0; i < height; i++)
	{
		vector<shared_ptr<BaseCell>> row;
		cells.push_back(row);
		for (int j = 0; j < width; j++)
		{
			shared_ptr<BaseCell> ec = make_shared<EmptyCell>();
			cells[i].push_back(ec);
		}
	}

	generateObstacles();
}

int Map::getHeight()
{
	return height;
}

int Map::getWidth()
{
	return width;
}

int Map::getCellCount()
{
	return width * height;
}

void Map::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			cout << cells[i][j]->toString();
		}
		cout << endl;
	}

	printSummary();
}

void Map::tryGenerateRandomValueCell()
{
	const int maxExclusiveValue = 10;
	int row = rand() % height;
	int column = rand() % width;
	int value = rand() % maxExclusiveValue;

	if (!isEmpty(row, column) || value == 0)
	{
		return;
	}

	cells[row][column] = make_shared<ValueCell>(value);
}

void Map::generateObstacles()
{
	// generate map borders
	for (int row = 0; row < height; row++)
	{
		for (int column = 0; column < width; column++)
		{
			if (row == 0 || column == 0 || row + 1 == height || column + 1 == width)
			{
				cells[row][column] = make_shared<ObstacleCell>();
			}
		}
	}

	float obstaclesProportion = (float)1 / 5;
	int totalObstacles = (int)round(obstaclesProportion * getCellCount());

	for (int i = 0; i < totalObstacles; i++)
	{
		int row = rand() % height;
		int column = rand() % width;

		if (isEmpty(row, column))
		{
			cells[row][column] = make_shared<ObstacleCell>();
		}
	}
}

void Map::printSummary()
{
	cout << "\n\n\n";

	for (int i = 0; i < snakes.size(); i++)
	{
		shared_ptr<BaseSnake> snake = snakes[i];
		cout << snake->getName() << " : " << snake->getPoints() << endl;
	}
}

bool Map::isEmpty(int row, int column)
{
	return dynamic_pointer_cast<EmptyCell>(cells[row][column]) != NULL;
}
