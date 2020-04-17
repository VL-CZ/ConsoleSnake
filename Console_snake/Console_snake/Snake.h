#pragma once
#include<iostream>
#include "Direction.h"

class BaseSnake
{
public:
	BaseSnake(std::string name);

	int getPoints();
	std::string getName();
	Direction getDirection();
	void setDirection(Direction d);

	virtual void move() = 0;
protected:
	int points;
	Direction direction;
private:
	std::string name;
	/*std::shared_ptr<Map> map;*/
};

class UserSnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	UserSnake(std::string name);
private:
	char moveUpKey = 'w';
	char moveDownKey = 's';
	char moveLeftKey = 'a';
	char moveRightKey = 'd';

	void tryChangeDirection();
};

class AISnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	AISnake(std::string name);
};