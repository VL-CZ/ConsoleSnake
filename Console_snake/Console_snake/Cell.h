#pragma once
#include <string>
#include "Direction.h"

// classes representing different types of cells

class BaseCell 
{
public:
	virtual std::string toString() = 0;
};

class ObstacleCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};

class EmptyCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};

class ValueCell : public BaseCell 
{
	// Inherited via BaseCell
	virtual std::string toString() override;

public:
	ValueCell(int value);

	int getValue();
private:
	int value;
};

// snake cells

class SnakeBodyCell : public BaseCell 
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};

class SnakeHeadCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override = 0;
};

class AISnakeHeadCell : public SnakeHeadCell
{
	// Inherited via SnakeHeadCell
	virtual std::string toString() override;
};

class UserSnakeHeadCell : public SnakeHeadCell
{
	// Inherited via SnakeHeadCell
	virtual std::string toString() override;

public:
	UserSnakeHeadCell(Direction d);
private:
	Direction orientation;
};