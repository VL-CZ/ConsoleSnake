#include "Snake.h"

void UserSnake::move()
{
}

UserSnake::UserSnake(std::string name) : BaseSnake(name)
{
}

void AISnake::move()
{
}

AISnake::AISnake(std::string name) : BaseSnake(name)
{
}

BaseSnake::BaseSnake(std::string name): name(name), points(0)
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
