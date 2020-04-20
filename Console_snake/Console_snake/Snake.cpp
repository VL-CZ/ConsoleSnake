#include "Snake.h"
#include <conio.h>
#include <memory>
using namespace std;

void UserSnake::move()
{
	tryToChangeDirection();

	switch (direction)
	{
	case Direction::Up:
		headPosition.row--;
		break;
	case Direction::Left:
		headPosition.column--;
		break;
	case Direction::Right:
		headPosition.column++;
		break;
	case Direction::Down:
		headPosition.row++;
		break;
	}
	auto head = make_shared<UserSnakeHeadCell>();
	map->cells[headPosition.row][headPosition.column] = head;
}

UserSnake::UserSnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map) : 
	BaseSnake(name, position, direction, map)
{
}

void UserSnake::tryToChangeDirection()
{
	if (_kbhit())
	{
		char pressedKey = _getch();

		if (pressedKey == moveUpKey)
		{
			direction = Direction::Up;
		}
		else if (pressedKey == moveLeftKey)
		{
			direction = Direction::Left;
		}
		else if (pressedKey == moveDownKey)
		{
			direction = Direction::Down;
		}
		else if (pressedKey == moveRightKey)
		{
			direction = Direction::Right;
		}
	}
}

void AISnake::move()
{
}

AISnake::AISnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map) : 
	BaseSnake(name, position, direction, map)
{
}

BaseSnake::BaseSnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map) :
	name(name), points(0), direction(direction), headPosition(position), map(map)
{
	auto headCell = make_shared<UserSnakeHeadCell>();
	map->cells[headPosition.row][headPosition.column] = headCell;
}

int BaseSnake::getPoints()
{
	return points;
}

std::string BaseSnake::getName()
{
	return name;
}

std::shared_ptr<BaseCell> BaseSnake::getHead()
{
	return cells[0];
}
