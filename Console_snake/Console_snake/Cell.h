#pragma once
#include <string>

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
private:
	int value;
};

class SnakeBodyCell : public BaseCell 
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};

class AISnakeHeadCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};

class UserSnakeHeadCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;
};