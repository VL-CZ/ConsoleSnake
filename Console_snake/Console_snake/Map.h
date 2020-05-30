#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "MapCoordinates.h"
#include "Direction.h"
#include <set>

class Map
{
public:
	
	Map(int height, int width, float obstacleProportion);

	int getHeight();
	int getWidth();
	int getCellCount();

	void print();

	/// <summary>
	/// try to generate random value cell somewhere in the map
	/// </summary>
	void tryGenerateRandomValueCell();

	bool isEmpty(MapPosition position);
	
	std::shared_ptr<BaseCell> getCellAtPosition(MapPosition position);
	
	void setCellAtPosition(MapPosition position, std::shared_ptr<BaseCell> cell);
	
	/// <summary>
	/// get cell next to position at the specified direction
	/// </summary>
	/// <param name="position"></param>
	/// <param name="direction"></param>
	/// <returns></returns>
	std::shared_ptr<BaseCell> getAdjacentCell(MapPosition position, Direction direction);
	
	/// <summary>
	/// get adjacent map positions
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	std::vector<MapPosition> getAdjacentCellPositions(MapPosition position);

	/// <summary>
	/// try to get value from specified position
	/// </summary>
	/// <param name="position"></param>
	/// <param name="value"></param>
	/// <returns>true if the cell has value</returns>
	bool tryGetValue(MapPosition position, int& value);

	/// <summary>
	/// get square of map
	/// </summary>
	/// <param name="centralPosition"></param>
	/// <param name="squareSize">width of the new square</param>
	/// <returns></returns>
	std::shared_ptr<Map> getSquare(MapPosition centralPosition, int squareSize);

	/// <summary>
	/// get random valid start position for snake oriented in selected direction
	/// </summary>
	/// <param name="snakeHeadDirection"></param>
	/// <returns></returns>
	MapPosition getValidStartPosition(Direction snakeHeadDirection);
private:
	int height;
	int width;
	std::vector<std::vector<std::shared_ptr<BaseCell>>> cells;
	
	/// <summary>
	/// generate obstacles into map
	/// </summary>
	/// <param name="obstacleProportion">approximate proportion of obstacles in the map (0 -> 0 %, 1 -> 100 %)</param>
	void generateObstacles(float obstacleProportion);

	bool isEmpty(int row, int column);

	bool isInMap(MapPosition position);

	/// <summary>
	/// check if this position is a valid start position for snake oriented in selected direction
	/// (e.g. at least three cells in front of snake's head are empty)
	/// </summary> 
	/// <param name="mp"></param>
	/// <param name="headDirection"></param>
	/// <returns></returns>
	bool isGoodStartPosition(MapPosition mp, Direction headDirection);
};

