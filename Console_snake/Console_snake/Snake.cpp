#include "Snake.h"
#include <conio.h>
#include <memory>
using namespace std;

#pragma region UserSnake

void UserSnake::move()
{
	tryToChangeDirection();

	executeMove();
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

#pragma endregion

#pragma region AISnake

void AISnake::move()
{
	this->direction = Direction::Left;

	executeMove();
}

AISnake::AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	BaseSnake(name, position, direction, map)
{
}

#pragma endregion

#pragma region BaseSnake

BaseSnake::BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	name(name), points(0), direction(direction), headPosition(position), map(map), alive(true)
{
	cells.push(headPosition);
	auto headCell = make_shared<UserSnakeHeadCell>();
	map->setCellAtPosition(headPosition, headCell);

	// test
	MapPosition bodyPosition(headPosition.row, headPosition.column + 1);
	cells.push(bodyPosition);
	auto bodyCell = make_shared<SnakeBodyCell>();
	map->setCellAtPosition(bodyPosition, bodyCell);
}

int BaseSnake::getPoints()
{
	return points;
}

std::string BaseSnake::getName()
{
	return name;
}

bool BaseSnake::isAlive()
{
	return alive;
}

void BaseSnake::executeMove()
{
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

		int points;
		bool hasValue = map->tryGetValue(newPosition, points);

		map->setCellAtPosition(headPosition, body);
		map->setCellAtPosition(newPosition, head);

		headPosition = newPosition;
		cells.push(headPosition);

		if (!hasValue)
		{
			auto emptyCell = make_shared<EmptyCell>();
			map->setCellAtPosition(cells.front(), emptyCell);
			cells.pop();
		}
		else
		{
			this->points += points;
		}
	}
	else
	{
		alive = false;
	}
}

#pragma endregion