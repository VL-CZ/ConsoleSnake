#pragma once
#include<iostream>
#include "Map.h"
#include "Snake.h"
class Game
{
public:
	void play();
private:
	std::shared_ptr<Map> map;
	std::vector<std::shared_ptr<BaseSnake>> snake;

	void update();
};

