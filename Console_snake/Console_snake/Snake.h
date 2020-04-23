#pragma once
#include <iostream>
#include <vector>
#include "Direction.h"
#include "Cell.h"
#include "Map.h"
#include "MapCoordinates.h"
#include <queue>

class BaseSnake
{
public:
	BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map);

	int getPoints();
	std::string getName();

	virtual void move() = 0;
protected:
	int points;
	Direction direction;
	std::queue<MapPosition> cells;
	MapPosition headPosition;
	std::shared_ptr<Map> map;

	void executeMove();
private:
	std::string name;
};

class UserSnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	UserSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map);
private:
	char moveUpKey = 'w';
	char moveDownKey = 's';
	char moveLeftKey = 'a';
	char moveRightKey = 'd';

	void tryToChangeDirection();
};

class AISnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map);
};