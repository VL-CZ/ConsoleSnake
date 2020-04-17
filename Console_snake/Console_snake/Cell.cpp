#include "Cell.h"
using namespace std;

std::string EmptyCell::toString()
{
	return " ";
}

std::string ObstacleCell::toString()
{
	return "#";
}

std::string ValueCell::toString()
{
	return to_string(value);
}

ValueCell::ValueCell(int value) : value(value)
{
}

std::string SnakeBodyCell::toString()
{
	return "O";
}

std::string AISnakeHeadCell::toString()
{
	return "@";
}

std::string UserSnakeHeadCell::toString()
{
	return "@";
}
