#pragma once
#include<iostream>

class BaseSnake
{
public:
	BaseSnake(std::string name);

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

public:
	UserSnake(std::string name);
};

class AISnake : public BaseSnake 
{
	// Inherited via BaseSnake
	virtual void move() override;

public:
	AISnake(std::string name);
};