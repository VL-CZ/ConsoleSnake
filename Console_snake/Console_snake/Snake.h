#pragma once
#include<iostream>
#include "Direction.h"
#include "Cell.h"
#include <vector>

class BaseSnake
{
public:
	BaseSnake(std::string name);

	int getPoints(); 
	std::string getName();
	std::shared_ptr<BaseCell> getHead();

	virtual void move() = 0;
protected:
	int points;
	Direction direction;
	std::vector<std::shared_ptr<BaseCell>> cells;
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

	void tryToChangeDirection();
};

class AISnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	AISnake(std::string name);
};