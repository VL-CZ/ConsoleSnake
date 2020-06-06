#pragma once
#include "Direction.h"

/// <summary>
/// struct representing position (row, column) in the map
/// </summary>
struct MapPosition
{
	int row;
	int column;

	MapPosition(int row, int column) : row(row), column(column)
	{}

	MapPosition AddDirection(Direction d)
	{
		switch (d)
		{
		case Direction::Left:
			return MapPosition(row, column - 1);
		case Direction::Right:
			return MapPosition(row, column + 1);
		case Direction::Up:
			return MapPosition(row - 1, column);
		case Direction::Down:
			return MapPosition(row + 1, column);
		}
	}


	bool operator==(const MapPosition& other)
	{
		return row == other.row && column == other.column;
	}

	bool operator < (const MapPosition& other) const
	{
		return (row < other.row  || (row == other.row && column < other.column));
	}
};

