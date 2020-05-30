#pragma once
#include<iostream>
#include<memory>
#include<Windows.h>
#include "Map.h"
#include "Snake.h"
#include "Direction.h"
class Game
{
public:
	Game();

	/// <summary>
	/// start the game
	/// </summary>
	void play();
private:
	/// <summary>
	/// is game in progess?
	/// </summary>
	bool inProgress;

	/// <summary>
	/// console output
	/// </summary>
	const HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<BaseSnake>> snakes;

	/// <summary>
	/// execute move of all snakes
	/// </summary>
	void update();

	void initialize();

	/// <summary>
	/// print snake points
	/// </summary>
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