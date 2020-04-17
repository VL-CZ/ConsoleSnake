#pragma once
#include<iostream>
#include "Map.h"
#include "Snake.h"
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
};

