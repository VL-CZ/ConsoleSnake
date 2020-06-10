#pragma once
#include <string>
#include "Direction.h"

// classes representing different types of cells

class BaseCell
{
public:
	virtual std::string toString() = 0;

	/// <summary>
	/// returns if the cell is safe to go (e.g. it's empty or it has points)
	/// </summary>
	/// <returns></returns>
	virtual bool isSafeToGo() = 0;

	/// <summary>
	/// try to get points value from the cell
	/// </summary>
	/// <param name="value">extracted value</param>
	/// <returns>true, if it has value; otherwise returns false</returns>
	virtual bool tryGetValue(int& value);

	/// <summary>
	/// is this cell snake head?
	/// </summary>
	/// <returns></returns>
	virtual bool isSnakeHead();
};

class ObstacleCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;

	// Inherited via BaseCell
	virtual bool isSafeToGo() override;
};

class EmptyCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;

	// Inherited via BaseCell
	virtual bool isSafeToGo() override;
};

class ValueCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override;

	// Inherited via BaseCell
	virtual bool isSafeToGo() override;
	
	bool tryGetValue(int& value) override;

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

	// Inherited via BaseCell
	virtual bool isSafeToGo() override;
};

class SnakeHeadCell : public BaseCell
{
	// Inherited via BaseCell
	virtual std::string toString() override = 0;

	// Inherited via BaseCell
	virtual bool isSafeToGo() override;

	virtual bool isSnakeHead() override;
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