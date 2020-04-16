#pragma once
#include<iostream>

class BaseSnake
{
public:
	int getPoints();
	std::string getName();

	virtual void move() = 0;
protected:
	int points;
	std::string name;
	/*std::shared_ptr<Map> map;*/
};

class UserSnake : public BaseSnake
{
	// Inherited via BaseSnake
	virtual void move() override;
};

class AISnake : public BaseSnake 
{
	// Inherited via BaseSnake
	virtual void move() override;
};