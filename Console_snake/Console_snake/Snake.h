#pragma once
#include <iostream>
#include <vector>
#include "Direction.h"
#include "Cell.h"
#include "Map.h"
#include "MapCoordinates.h"
#include <queue>
#include <map>

class BaseSnake
{
public:
	BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map);

	int getPoints();
	std::string getName();
	bool isAlive();

	/// <summary>
	/// move the snake
	/// </summary>
	virtual void move() = 0;

	/// <summary>
	/// get new instance of snake head type
	/// </summary>
	/// <returns></returns>
	virtual std::shared_ptr<SnakeHeadCell> getNewHeadCell() = 0;

protected:

	int points;

	/// <summary>
	/// current direction
	/// </summary>
	Direction direction;

	/// <summary>
	/// list of snake cell positions
	/// </summary>
	std::queue<MapPosition> cells;

	MapPosition headPosition;

	std::shared_ptr<Map> map;

	void executeMove();
private:
	std::string name;
	bool alive;

	/// <summary>
	/// remove snake from map (replace all its body cells by points with value 9)
	/// and mark that it's not alive
	/// </summary>
	void die();
};

class UserSnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

	// Inherited via BaseSnake
	virtual std::shared_ptr<SnakeHeadCell> getNewHeadCell() override;

public:
	UserSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map);
private:
	// keys for movement
	char moveUpKey = 'w';
	char moveDownKey = 's';
	char moveLeftKey = 'a';
	char moveRightKey = 'd';

	/// <summary>
	/// change direction if key pressed 
	/// </summary>
	void tryToChangeDirection();
};

class AISnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;

	// Inherited via BaseSnake
	virtual std::shared_ptr<SnakeHeadCell> getNewHeadCell() override;

private:
	// priorities
	const int anotherSnakeHeadPriority = -150;
	const int wallOrSnakePriority = -25;
	const int oneValuePriority = 100;

	/// <summary>
	/// size of map view
	/// </summary>
	int viewSize;

	/// <summary>
	/// get priority map
	/// </summary>
	/// <returns></returns>
	std::map<Direction, int> getPriorities();

	/// <summary>
	/// add priorities of adjacent cells into priorityMap.
	/// Cells next to centerCell have priority equal to (centerPriority/2)
	/// </summary>
	/// <param name="map"></param>
	/// <param name="priorityMap"></param>
	/// <param name="centerCell"></param>
	/// <param name="centerPriority"></param>
	void addAdjacentCellsPriorities(std::shared_ptr<Map> map, std::vector<std::vector<int>>& priorityMap, MapPosition centerCell, int centerPriority);
public:
	AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map, int viewSize = 5);
};