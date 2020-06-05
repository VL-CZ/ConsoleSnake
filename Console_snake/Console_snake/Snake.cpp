#include "Snake.h"
#include "Cell.h"
#include <conio.h>
#include <memory>
using namespace std;

#pragma region UserSnake

void UserSnake::move()
{
	tryToChangeDirection();

	executeMove();
}

UserSnake::UserSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	BaseSnake(name, position, direction, map)
{
	// place snake head at position
	auto headCell = make_shared<UserSnakeHeadCell>();
	map->setCellAtPosition(headPosition, headCell);
}

void UserSnake::tryToChangeDirection()
{
	if (_kbhit())
	{
		char pressedKey = _getch();

		if (pressedKey == moveUpKey)
		{
			direction = Direction::Up;
		}
		else if (pressedKey == moveLeftKey)
		{
			direction = Direction::Left;
		}
		else if (pressedKey == moveDownKey)
		{
			direction = Direction::Down;
		}
		else if (pressedKey == moveRightKey)
		{
			direction = Direction::Right;
		}
	}
}

std::shared_ptr<SnakeHeadCell> UserSnake::getHeadCell()
{
	return make_shared<UserSnakeHeadCell>();
}

#pragma endregion

#pragma region AISnake

void AISnake::move()
{
	auto priorities = getPriorities();

	int max_priority = INT32_MIN;

	// get max priority
	for (auto p : priorities)
	{
		if (p.second > max_priority)
			max_priority = p.second;
	}

	vector<Direction> max_priorities;

	// get all directions with max priority
	for (auto p : priorities)
	{
		if (p.second == max_priority)
		{
			max_priorities.push_back(p.first);
		}
	}

	int randomInt = rand() % max_priorities.size();

	direction = max_priorities[randomInt];
	executeMove();
}

std::map<Direction, int> AISnake::getPriorities()
{
	auto mapSquare = map->getSquare(headPosition, viewSize);

	auto priorityMap = vector<vector<int>>();

	// init priority map
	for (int i = 0; i < viewSize; i++)
	{
		auto row = vector<int>();
		for (int j = 0; j < viewSize; j++)
		{
			row.push_back(0);
		}
		priorityMap.push_back(row);
	}

	MapPosition centerSquarePosition(viewSize / 2, viewSize / 2);
	for (int i = 0; i < viewSize; i++)
	{
		for (int j = 0; j < viewSize; j++)
		{
			if (i == viewSize / 2 && j == viewSize / 2)
				continue;

			MapPosition currentPosition(i, j);
			auto c = mapSquare->getCellAtPosition(currentPosition);


			// obstacle or snake body cell
			if (dynamic_pointer_cast<ObstacleCell>(c) != NULL || dynamic_pointer_cast<SnakeBodyCell>(c) != NULL)
			{
				priorityMap[currentPosition.row][currentPosition.column] += wallOrSnakePriority;
				addAdjacentCellsPriorities(mapSquare,priorityMap, currentPosition, wallOrSnakePriority);
			}
			// snake head
			else if (dynamic_pointer_cast<SnakeHeadCell>(c) != NULL)
			{
				priorityMap[currentPosition.row][currentPosition.column] += anotherSnakeHeadPriority;
				addAdjacentCellsPriorities(mapSquare, priorityMap, currentPosition, anotherSnakeHeadPriority);
			}
			else if (dynamic_pointer_cast<ValueCell>(c) != NULL)
			{
				auto valueCell = dynamic_pointer_cast<ValueCell>(c);
				int priority = valueCell->getValue() * oneValuePriority;
				priorityMap[currentPosition.row][currentPosition.column] += priority;
				addAdjacentCellsPriorities(mapSquare, priorityMap, currentPosition, priority);
			}
		}
	}

	int crow = centerSquarePosition.row;
	int ccol = centerSquarePosition.column;

	auto priorites = std::map<Direction, int>();
	priorites[Direction::Left] = priorityMap[crow][ccol - 1];
	priorites[Direction::Right] = priorityMap[crow][ccol + 1];
	priorites[Direction::Up] = priorityMap[crow - 1][ccol];
	priorites[Direction::Down] = priorityMap[crow + 1][ccol];
	return priorites;
}

void AISnake::addAdjacentCellsPriorities(std::shared_ptr<Map> mapSquare,std::vector<std::vector<int>>& priorityMap, MapPosition centerCell, int centerCellPriority)
{
	auto adjacentCells = mapSquare->getAdjacentCellPositions(centerCell);

	for (auto c : adjacentCells)
	{
		priorityMap[c.row][c.column] += centerCellPriority / 2;
	}
}

AISnake::AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map, int viewSize)
	:BaseSnake(name, position, direction, map)
{
	this->viewSize = viewSize;

	// place snake head at position
	auto headCell = make_shared<AISnakeHeadCell>();
	map->setCellAtPosition(headPosition, headCell);
}

std::shared_ptr<SnakeHeadCell> AISnake::getHeadCell()
{
	return make_shared<AISnakeHeadCell>();
}

#pragma endregion

#pragma region BaseSnake

BaseSnake::BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	name(name), points(0), direction(direction), headPosition(position), map(map), alive(true)
{
	cells.push(headPosition);
	
	// place snake body at position

	MapPosition bodyPosition = headPosition.AddDirection(getOppositeDirection(direction));
	cells.push(bodyPosition);
	auto bodyCell = make_shared<SnakeBodyCell>();
	map->setCellAtPosition(bodyPosition, bodyCell);
}

int BaseSnake::getPoints()
{
	return points;
}

std::string BaseSnake::getName()
{
	return name;
}

bool BaseSnake::isAlive()
{
	return alive;
}

void BaseSnake::executeMove()
{
	MapPosition newPosition = headPosition;
	switch (direction)
	{
	case Direction::Up:
		newPosition.row--;
		break;
	case Direction::Left:
		newPosition.column--;
		break;
	case Direction::Right:
		newPosition.column++;
		break;
	case Direction::Down:
		newPosition.row++;
		break;
	}

	// execute move to position
	if (map->isEmpty(newPosition))
	{
		auto body = make_shared<SnakeBodyCell>();
		auto head = getHeadCell();

		int points;
		bool hasValue = map->tryGetValue(newPosition, points);

		map->setCellAtPosition(headPosition, body);
		map->setCellAtPosition(newPosition, head);

		headPosition = newPosition;
		cells.push(headPosition);

		// update points
		if (!hasValue)
		{
			auto emptyCell = make_shared<EmptyCell>();
			map->setCellAtPosition(cells.front(), emptyCell);
			cells.pop();
		}
		else
		{
			this->points += points;
		}
	}
	else
	{
		die();
	}
}

void BaseSnake::die()
{
	alive = false;
	while (!cells.empty())
	{
		MapPosition mp = cells.front();
		cells.pop();
		map->setCellAtPosition(mp, make_shared<ValueCell>(9));
	}
}

#pragma endregion