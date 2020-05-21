#include "Direction.h"

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
