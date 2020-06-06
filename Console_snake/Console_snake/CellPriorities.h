#pragma once
#include <memory>

struct CellPriorities
{
public:
	// priorities of walls, snakes and values
	static const int anotherSnakeHeadPriority = -10000; // it's not INT_MIN, because priorities are added (e.g. if a cell is between two walls, its priority is -20000)
	static const int wallOrSnakePriority = -10000;
	static const int oneValuePriority = 100;

	// priorities of cells next to walls, snakes and values
	static const int nextToAnotherSnakeHeadPriority = -100;
	static const int nextToWallOrSnakePriority = -25;
	static const int nextToOneValuePriority = 50;

	// priorities in distance 2 are half of distance one priorities
};