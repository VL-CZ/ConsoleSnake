#include "Snake.h"
#include <conio.h>

void UserSnake::move()
{
	tryToChangeDirection();
	

}

UserSnake::UserSnake(std::string name) : BaseSnake(name)
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

AISnake::AISnake(std::string name) : BaseSnake(name)
{
}

BaseSnake::BaseSnake(std::string name) : name(name), points(0), direction(Direction::Left)
{
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
