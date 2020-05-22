#pragma once
#include <vector>
#include <set>

enum class Direction {Left, Right, Up, Down};

Direction getOppositeDirection(Direction d);

std::vector<Direction> getAllDirections();