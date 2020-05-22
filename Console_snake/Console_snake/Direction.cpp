#include "Direction.h"
using namespace std;

Direction getOppositeDirection(Direction d)
{
	switch (d)
	{
	case Direction::Left:
		return Direction::Right;
	case Direction::Right:
		return Direction::Left;
	case Direction::Up:
		return Direction::Down;
	case Direction::Down:
		return Direction::Up;
	}
}

std::vector<Direction> getAllDirections()
{
	auto direcitons = std::vector<Direction>();
	direcitons.push_back(Direction::Left);
	direcitons.push_back(Direction::Right);
	direcitons.push_back(Direction::Up);
	direcitons.push_back(Direction::Down);

	return direcitons;
}
