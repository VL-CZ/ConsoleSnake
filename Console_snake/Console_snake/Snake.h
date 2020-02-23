#pragma once
#include<iostream>
#include "Map.h"

class BaseSnake
{
public:
	virtual void move() = 0;
private:
	std::shared_ptr<Map> map;
};

class UserSnake : BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;
};

class AISnake : BaseSnake 
{
	// Inherited via BaseSnake
	virtual void move() override;
};