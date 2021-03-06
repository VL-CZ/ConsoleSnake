#include "Map.h"
#include <time.h>
using namespace std;

Map::Map(int height, int width, float obstacleProportion)
{
	this->height = height;
	this->width = width;

	// init cells
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

std::shared_ptr<BaseCell> Map::getCellAtPosition(MapPosition position)
{
	return cells[position.row][position.column];
}

void Map::setCellAtPosition(MapPosition position, std::shared_ptr<BaseCell> cell)
{
	cells[position.row][position.column] = cell;
}

std::shared_ptr<BaseCell> Map::getAdjacentCell(MapPosition position, Direction direction)
{
	try
	{
		MapPosition mp = position;
		switch (direction)
		{
		case Direction::Left:
			mp = MapPosition(mp.row, mp.column - 1);
			break;
		case Direction::Right:
			mp = MapPosition(mp.row, mp.column + 1);
			break;
		case Direction::Up:
			mp = MapPosition(mp.row - 1, mp.column);
			break;
		case Direction::Down:
			mp = MapPosition(mp.row + 1, mp.column);
			break;
		}

		return getCellAtPosition(mp);
	}
	catch (exception e)
	{
		return NULL;
	}
}

std::vector<MapPosition> Map::getAdjacentCellPositions(MapPosition position)
{
	auto adjacentCells = vector<MapPosition>();

	int crow = position.row;
	int ccol = position.column;

	for (auto d : getAllDirections())
	{
		MapPosition mp = position.AddDirection(d);
		if (isInMap(mp))
		{
			adjacentCells.push_back(mp);
		}
	}

	return adjacentCells;
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
				// we are out of map
				row.push_back(make_shared<ObstacleCell>());
			}
		}
		cutMap.push_back(row);
	}

	auto mapSquare = make_shared<Map>(squareSize, squareSize, 0);
	mapSquare->cells = cutMap;
	return mapSquare;
}

MapPosition Map::getValidStartPosition(Direction snakeHeadDirection)
{
	bool isValid = false;

	while (isValid == false)
	{
		int row = rand() % height;
		int col = rand() % width;
		MapPosition mp = MapPosition(row, col);

		if (isGoodStartPosition(mp, snakeHeadDirection))
			return mp;
	}
}

bool Map::isGoodStartPosition(MapPosition mp, Direction headDirection)
{
	auto p1 = mp.AddDirection(headDirection);
	auto p2 = p1.AddDirection(headDirection);
	auto p3 = p2.AddDirection(headDirection);

	Direction reversedDirection = getOppositeDirection(headDirection);
	auto tail = mp.AddDirection(reversedDirection);
	auto behindTail = tail.AddDirection(reversedDirection);

	return isEmpty(mp) && isEmpty(p1) && isEmpty(p2) && isEmpty(p3) && isEmpty(tail) && isEmpty(behindTail);
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

	// randomly generate some obstacles
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

bool Map::isEmpty(MapPosition position)
{
	return isEmpty(position.row, position.column);
}

bool Map::isEmpty(int row, int column)
{
	return isInMap(MapPosition(row, column)) && // it's in map
		cells[row][column]->isSafeToGo();
}

bool Map::isInMap(MapPosition position)
{
	return position.row >= 0 && position.row < height&& position.column >= 0 && position.column < width;
}
