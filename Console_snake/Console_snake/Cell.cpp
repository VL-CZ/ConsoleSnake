#include "Cell.h"
using namespace std;

std::string EmptyCell::toString()
{
	return " ";
}

bool EmptyCell::isSafeToGo()
{
	return true;
}

std::string ObstacleCell::toString()
{
	return "#";
}

bool ObstacleCell::isSafeToGo()
{
	return false;
}

std::string ValueCell::toString()
{
	return to_string(value);
}

ValueCell::ValueCell(int value) : value(value)
{
}

int ValueCell::getValue()
{
	return value;
}

bool ValueCell::isSafeToGo()
{
	return true;
}

bool ValueCell::tryGetValue(int& value)
{
	value = this->value;
	return true;
}

std::string SnakeBodyCell::toString()
{
	return "O";
}

bool SnakeBodyCell::isSafeToGo()
{
	return false;
}

std::string AISnakeHeadCell::toString()
{
	return "@";
}

std::string UserSnakeHeadCell::toString()
{
	switch (orientation)
	{
	case Direction::Left:
		return "<";
	case Direction::Right:
		return ">";
	case Direction::Up:
		return "A";
	case Direction::Down:
		return "V";
	}
}

UserSnakeHeadCell::UserSnakeHeadCell(Direction d) : orientation(d)
{
}

bool SnakeHeadCell::isSafeToGo()
{
	return false;
}

bool SnakeHeadCell::isSnakeHead()
{
	return true;
}

bool BaseCell::tryGetValue(int& value)
{
	return false;
}

bool BaseCell::isSnakeHead()
{
	return false;
}
