#include "Snake.h"
#include <conio.h>
#include <memory>
using namespace std;

void UserSnake::move()
{
	tryToChangeDirection();

	MapPosition newPosition = headPosition;
	switch (direction)
	{
	case Direction::Up:
		newPosition.row--;
		break;
	case Direction::Left:
		newPosition.column--;
		break;
	case Direction::Right:
		newPosition.column++;
		break;
	case Direction::Down:
		newPosition.row++;
		break;
	}

	if (map->isEmpty(newPosition))
	{
		auto body = make_shared<SnakeBodyCell>();
		auto head = make_shared<UserSnakeHeadCell>();

		map->SetCellAtPosition(headPosition, body);
		map->SetCellAtPosition(newPosition, head);

		headPosition = newPosition;
	}
}

UserSnake::UserSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
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

AISnake::AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	BaseSnake(name, position, direction, map)
{
}

BaseSnake::BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	name(name), points(0), direction(direction), headPosition(position), map(map)
{
	auto headCell = make_shared<UserSnakeHeadCell>();
	map->SetCellAtPosition(headPosition, headCell);
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
