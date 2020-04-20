#pragma once
#include <iostream>
#include <vector>
#include "Direction.h"
#include "Cell.h"
#include "Map.h"
#include "MapCoordinates.h"

class BaseSnake
{
public:
	BaseSnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map);

	int getPoints();
	std::string getName();
	std::shared_ptr<BaseCell> getHead();

	virtual void move() = 0;
protected:
	int points;
	Direction direction;
	std::vector<std::shared_ptr<BaseCell>> cells;
	MapCoordinates headPosition;
	std::shared_ptr<Map> map;
private:
	std::string name;
};

class UserSnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	UserSnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map);
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
	AISnake(std::string name, MapCoordinates position, Direction direction, std::shared_ptr<Map> map);
};