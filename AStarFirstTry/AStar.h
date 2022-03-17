#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Vector2.h"
#include "Node.h"
#include "List.h"
#include "Graph.h"
#include "AStartUtility.h"

class AStar
{
public:
	AStar(const int width, const int height);
	AStar();
	~AStar() {};

	std::vector<Vector2> GetPath(Vector2 startPos, Vector2 endPos);

	Graph aStarGrid;
	const int GRID_WIDTH;
	const int GRID_HEIGHT;

	Node startNode;
	Node goalNode;

	List openList;
	List closedList;

	Node current;

private:
	std::vector<Vector2> CalculatePath();
};

