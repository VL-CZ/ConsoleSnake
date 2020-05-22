#pragma once
#include<iostream>
#include<memory>
#include "Map.h"
#include "Snake.h"
#include "Direction.h"
class Game
{
public:
	Game();

	void play();
private:
	bool running;
	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<BaseSnake>> snakes;

	void update();
	void initialize();
	void printSummary();
};



// FUNCTIONS:
Direction getRandomDirection();

// compare snakes by points descending
struct SnakePointsComparer
{
	bool operator()(const std::shared_ptr<BaseSnake>& x, const std::shared_ptr<BaseSnake>& y)
	{
		return x->getPoints() > y->getPoints();
	}
};
