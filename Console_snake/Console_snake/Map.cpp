#include "Map.h"
#include <time.h>
using namespace std;

Map::Map(int height, int width, float obstacleProportion)
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

	generateObstacles(obstacleProportion);
}

#pragma region Getters

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

#pragma endregion

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

bool Map::isEmpty(MapPosition position)
{
	return isEmpty(position.row, position.column);
}

std::shared_ptr<BaseCell> Map::getCellAtPosition(MapPosition position)
{
	return cells[position.row][position.column];
}

void Map::setCellAtPosition(MapPosition position, std::shared_ptr<BaseCell> cell)
{
	cells[position.row][position.column] = cell;
}

bool Map::tryGetValue(MapPosition position, int& value)
{
	auto valueCell = dynamic_pointer_cast<ValueCell>(getCellAtPosition(position));
	if (valueCell != NULL)
	{
		value = valueCell->getValue();
		return true;
	}
	else
	{
		return false;
	}
}

std::shared_ptr<Map> Map::getSquare(MapPosition centralPosition, int squareSize)
{
	int upperBound = squareSize / 2;
	int lowerBound = (-1) * upperBound;

	auto cutMap = vector<vector<shared_ptr<BaseCell>>>();

	for (int i = lowerBound; i <= upperBound; i++)
	{
		auto row = vector<shared_ptr<BaseCell>>();
		for (int j = lowerBound; j <= upperBound; j++)
		{
			MapPosition currentPosition(centralPosition.row + i, centralPosition.column + j);

			if (isInMap(currentPosition))
			{
				row.push_back(getCellAtPosition(currentPosition));
			}
			else
			{
				row.push_back(make_shared<ObstacleCell>());
			}
		}
		cutMap.push_back(row);
	}

	auto mapSquare = make_shared<Map>(squareSize, squareSize, 0);
	mapSquare->cells = cutMap;
	return mapSquare;
}

void Map::generateObstacles(float obstacleProportion)
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

	int totalObstacles = (int)round(obstacleProportion * getCellCount());

	srand(time(NULL));

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

bool Map::isEmpty(int row, int column)
{
	return dynamic_pointer_cast<EmptyCell>(cells[row][column]) != NULL ||
		dynamic_pointer_cast<ValueCell>(cells[row][column]) != NULL;
}

bool Map::isInMap(MapPosition position)
{
	return position.row >= 0 && position.row < height&& position.column >= 0 && position.column < width;
}
