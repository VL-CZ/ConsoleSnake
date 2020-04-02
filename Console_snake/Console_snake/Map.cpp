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

void Map::placeObstacleAt(int row, int column)
{
	cells[row][column] = make_shared<ObstacleCell>();
}

void Map::generateObstacles()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((i + j) % 5 == 0)
			{
				cells[i][j] = make_shared<ObstacleCell>();
			}
			if ((i + j) % 7 == 0)
			{
				cells[i][j] = make_shared<ValueCell>(j);
			}
		}
	}
}
