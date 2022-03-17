#pragma once
#include <vector>

#include "Node.h"


class Graph
{
public:

    Graph(int width, int height);
    Graph();
    ~Graph();

    int graphWidth;
    int graphHeight;

    std::vector<Node> graphNodes{};

    double GetCostOfNode(Node current, Node  next);

    Node& GetNode(Vector2 node);
    Node& GetNode(Node& node);


    std::vector<Node> GetAroundNodes(Node current);

    void AddObstacles(std::vector<Vector2> positions);
    void AddObstacle(Vector2 position);

};

