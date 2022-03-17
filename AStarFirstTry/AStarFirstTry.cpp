#include <iostream>


#include "AStar.h"


using namespace std;



void DisplayGridWithCoord(Graph& graph, Node& goalNode, Node& startNode)
{
    for (int yy = 0; yy < graph.graphHeight; yy++)//Colognes
    {
        for (int xx = 0; xx < graph.graphWidth; xx++)//Lignes
        {


            if (xx == startNode.x && yy == startNode.y)
            {
                cout << "[  S ]";

            }
            else if (xx == goalNode.x && yy == goalNode.y)
            {
                cout << "[  G ]";

            }
            else if (!graph.GetNode(Vector2(xx, yy)).traversable)
            {
                cout << "[ " << " X " << "]";
            }
            else
            {
                cout << "[ " << xx << " " << yy << "]";

            }

        }
        cout << endl;

    }
}

void DisplayGridWithNodes(Graph& graph, Node& goalNode, Node& startNode, List& openList,List& closedList,List& path)
{
    for (int yy = 0; yy < graph.graphHeight; yy++)//Colognes
    {
        for (int xx = 0; xx < graph.graphWidth; xx++)//Lignes
        {


            if (xx == startNode.x && yy == startNode.y)
            {
                //nodeGraph.push_back(startNode);
                cout << "[ S ]";

            }
            else if (xx == goalNode.x && yy == goalNode.y)
            {
                // nodeGraph.push_back(goalNode);
                cout << "[ G ]";

            }


            else if (!graph.GetNode(Vector2(xx, yy)).traversable)
            {
                cout << "[ " << "X " << "]";
            }

            else   if (openList.IsInList(Vector2(xx, yy)))
            {

                if (openList.FindInList(Vector2(xx, yy)).cost > 99)
                {
                    cout << "[" << openList.FindInList(Vector2(xx, yy)).cost;
                }
                else
                {
                    cout << "[" << openList.FindInList(Vector2(xx, yy)).cost;

                }
                //Check si fait parti du path

                if (path.IsInList(Vector2(xx, yy)))
                {
                    cout << "@" << "]";

                }
                cout << "]";

                //cout << "[" << openList.FindInList(Vector2(xx, yy)).cameFrom->positon.x << " " << openList.FindInList(Vector2(xx, yy)).cameFrom->positon.y << "]";

            }

            else   if (closedList.IsInList(Vector2(xx, yy)))
            {
                string pathLetter = "";

                if (path.IsInList(Vector2(xx, yy)))
                {
                    pathLetter = "@}";

                }
                else
                {
                    if (closedList.FindInList(Vector2(xx, yy)).cost > 99)
                    {
                        pathLetter = "}";

                    }
                    else
                    {
                        pathLetter = " }";

                    }
                }
                cout << "{" << closedList.FindInList(Vector2(xx, yy)).cost << pathLetter;


                //cout << "{" << closedList.FindInList(Vector2(xx, yy)).cameFrom->positon.x << " " << closedList.FindInList(Vector2(xx, yy)).cameFrom->positon.y << "}";


            }
            else
            {
                cout << "[ " << "  " << "]";

            }

        }
        cout << endl;

    }

}

void ShowPath(Graph& graph, Node& current, Node& startNode,Node& goalNode, List& closedList)
{
    List path = List(); //Liste final pour le chemin

    //Show Path
    cout << endl << "______Path______" << endl;
    while (current != startNode)
    {
        path += current;
        current = closedList.FindInList(*current.cameFrom);
    }
    path += startNode;
    reverse(path.nodeList.begin(), path.nodeList.end());

    for (Node nd : path.nodeList)
    {
        cout << "    Node: " << nd.x << ":" << nd.y << " " << endl;

    }
    std::cout << std::endl;


    #pragma region ShowGrid
    for (int yy = 0; yy < graph.graphHeight; yy++)//Colognes
    {
        for (int xx = 0; xx < graph.graphWidth; xx++)//Lignes
        {
            if (xx == startNode.x && yy == startNode.y)
            {
                cout << "[ S ]";
            }
            else if (xx == goalNode.x && yy == goalNode.y)
            {
                cout << "[ G ]";
            }
            else if (!graph.GetNode(Vector2(xx, yy)).traversable)
            {
                cout << "[ " << "X " << "]";
            }
            else if (path.IsInList(Vector2(xx, yy)))
            {
                cout << "[ " << "@ " << "]";
            }
            else
            {
                cout << "[ " << "  " << "]";
            }
        }
        cout << endl;

    }
    #pragma endregion



}



void Init()
{
    //==========]Grid Setup[=================//
    const int GRID_WIDTH = 11;
    const int GRID_HEIGHT = 6;

    Graph graph(GRID_WIDTH, GRID_HEIGHT);//Créer la grille


    Node startNode = Node(Vector2(7, 4));
    startNode.cameFrom = &startNode;
    Node goalNode = Node(Vector2(4, 1));
    
    //Rajoute les obstacles
    vector<Vector2> obstacles = { Vector2(3,1),Vector2(2,2),Vector2(3,2) ,Vector2(4,2) ,Vector2(5,2) ,Vector2(6,2),Vector2(7,2),Vector2(8,2),Vector2(9,2), Vector2(5,3)};//,Vector2(10,2) };
    graph.AddObstacles(obstacles);

    //Affiche la grille
    DisplayGridWithCoord(graph, startNode, goalNode);

    //V

    List openList = List(); //Liste de nodes à check
    List closedList = List(); //Liste de node déjà check
    openList += startNode; //Rajoute le premier node à la liste open

    //Node actuel à check
    Node current;



    while (!openList.nodeList.empty())
    {
        current = openList.FindLowestValue();

        //===========]Debug[===========//
        /*
        cout<< endl << "Selected/Current Node = " << current.x<<" " << current.y <<" f_cost: "<<current.cost << endl;
        cout << "Dans la liste de choix: ";
        for (Node nd : openList.nodeList)
        {
            cout << nd.cost<<" ";
        }
        cout << endl;
        */
        //============================//
        

        openList -= current;
        closedList += current;

        if (current == goalNode)
        {
            break;//La recherche du chemin est fini
        }

        //C'est là qu'on va décider quel sera le prochain node à calculer
        for (Node& nextNode : graph.GetAroundNodes(current))
        {

            if (closedList.IsInList(nextNode) || !graph.GetNode(nextNode.positon).traversable) //Si le node à déjà été vérifié ou si il n'est pas traversable
            {
                continue; //Passe au voisin suivant
            }

            //On va définir le cout du prochain node
            double newCost = CalculateFCostOfNode(nextNode.positon,startNode.positon,goalNode.positon);
            
            if ( newCost < nextNode.cost || !openList.IsInList(nextNode))//Si le chemin à un plus petit cout que le node qui est check ou si il n'est pas dans open(donc pas encore check)
            {
                //Du coup c'est ce node qu'on va prendre
                nextNode.cost = newCost; //On va set son f cost            
                nextNode.cameFrom = &current; //Dit que le node vien du node current
                nextNode.cameFrom = &graph.GetNode(current); //Dit que le node vien du node current
                if (!openList.IsInList(nextNode))
                {
                    openList += nextNode;
                }
            }
        }

    }


    ShowPath(graph,current,startNode,goalNode,closedList);


}


int main()
{
    Init();
}


