#include "Snake.h"
#include "Cell.h"
#include <conio.h>
#include <memory>
#include <unordered_set>
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
	auto headCell = make_shared<UserSnakeHeadCell>(direction);
	map->setCellAtPosition(headPosition, headCell);
	cells.push(headPosition);
}

void UserSnake::tryToChangeDirection()
{
	if (_kbhit())
	{
		char pressedKey = _getch();
		Direction d;

		if (pressedKey == moveUpKey)
		{
			d = Direction::Up;
		}
		else if (pressedKey == moveLeftKey)
		{
			d = Direction::Left;
		}
		else if (pressedKey == moveDownKey)
		{
			d = Direction::Down;
		}
		else if (pressedKey == moveRightKey)
		{
			d = Direction::Right;
		}

		// cannot move backwards
		if (d != getOppositeDirection(direction))
		{
			direction = d;
		}
	}
}

std::shared_ptr<SnakeHeadCell> UserSnake::getNewHeadCell()
{
	return make_shared<UserSnakeHeadCell>(direction);
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
				priorityMap[currentPosition.row][currentPosition.column] += priorities.wallOrSnakePriority;
				addAdjacentCellsPriorities(mapSquare, priorityMap, currentPosition, priorities.nextToWallOrSnakePriority);
			}
			// snake head
			else if (dynamic_pointer_cast<SnakeHeadCell>(c) != NULL)
			{
				priorityMap[currentPosition.row][currentPosition.column] += priorities.anotherSnakeHeadPriority;
				addAdjacentCellsPriorities(mapSquare, priorityMap, currentPosition, priorities.nextToAnotherSnakeHeadPriority);
			}
			// value cell
			else if (dynamic_pointer_cast<ValueCell>(c) != NULL)
			{
				auto valueCell = dynamic_pointer_cast<ValueCell>(c);
				int priority = valueCell->getValue() * priorities.oneValuePriority;
				priorityMap[currentPosition.row][currentPosition.column] += priority;
				addAdjacentCellsPriorities(mapSquare, priorityMap, currentPosition, valueCell->getValue() * priorities.nextToOneValuePriority);
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

	// cannot move back
	priorites[getOppositeDirection(direction)] = INT32_MIN;

	return priorites;
}

void AISnake::addAdjacentCellsPriorities(std::shared_ptr<Map> mapSquare, std::vector<std::vector<int>>& priorityMap, MapPosition centerPosition, int adjacentCellPriority)
{
	auto adjacentCells = mapSquare->getAdjacentCellPositions(centerPosition);
	auto distanceTwoCells = vector<MapPosition>();

	for (auto c : adjacentCells)
	{
		// set priority
		priorityMap[c.row][c.column] += adjacentCellPriority;

		// get distance two cells
		auto adjacent = mapSquare->getAdjacentCellPositions(c);
		for (auto a : adjacent)
		{
			distanceTwoCells.push_back(a);
		}
	}

	// remove duplicates from distanceTwoCells
	sort(distanceTwoCells.begin(), distanceTwoCells.end());
	distanceTwoCells.erase(
		unique(distanceTwoCells.begin(), distanceTwoCells.end()), 
		distanceTwoCells.end());

	// remove center position
	distanceTwoCells.erase(
		remove(distanceTwoCells.begin(), distanceTwoCells.end(), centerPosition)
		, distanceTwoCells.end());

	// set distance 2 priority
	for (auto d : distanceTwoCells)
	{
		priorityMap[d.row][d.column] += adjacentCellPriority / 2;
	}
}

AISnake::AISnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map, int viewSize)
	:BaseSnake(name, position, direction, map)
{
	this->viewSize = viewSize;

	// place snake head at position
	auto headCell = make_shared<AISnakeHeadCell>();
	map->setCellAtPosition(headPosition, headCell);
	cells.push(headPosition);
}

std::shared_ptr<SnakeHeadCell> AISnake::getNewHeadCell()
{
	return make_shared<AISnakeHeadCell>();
}

#pragma endregion

#pragma region BaseSnake

BaseSnake::BaseSnake(std::string name, MapPosition position, Direction direction, std::shared_ptr<Map> map) :
	name(name), points(0), direction(direction), headPosition(position), map(map), alive(true)
{
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
		auto head = getNewHeadCell();

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