#include "Include/Graph.h"

/**
 * @brief Inserts a new Vertex object into Graph vertices 
 * 
 * @param y y coordinate of Vertex
 * @param x x coordinate of Vertex
 * @param neighbors list of coordinates of neighboring vectors
 * @param distance working variable: -2 for start, -3 for finish, 0 for rest
 */
void Graph::Insert(int y, int x, vector<pair<int, int>> neighbors, int distance)
{
    Vertex * vertex = new Vertex(y, x, distance);

    if (distance == -2)
        this->start = vertex;

    if (distance == -3)
        this->finish = vertex;

    this->vertices.push_back(vertex);

    for (int i = 0; i < neighbors.size(); i++)
    {
        for (auto v : this->vertices)
        {
            if (v->coords == neighbors[i])
            {
                vertex->neighbors.push_back(v);
                if (v != vertex)
                    v->neighbors.push_back(vertex);
                break;
            }
        }
    }
}

/**
 * @brief Prints the whole Graph - every Vertex, its coordinates, distance and neighbors - into the console
 * 
 */
void Graph::Print()
{
    cout << "Printing graph" << endl;
    for (auto v : this->vertices)
    {
        cout << "(x, y) \t" << v->coords.first << " " << v->coords.second << endl;
        cout << "distance " << v->distance << endl;
        cout << "neighbors:" << endl;
        for (int i = 0; i < v->neighbors.size(); i++)
        {
            cout << "   " << v->neighbors[i]->coords.first << " " << v->neighbors[i]->coords.second << endl;
        }
        cout << endl;
    }
}

/**
 * @brief Returns the distance of a Vertex specified by its coordinates
 * 
 * @param y y coordinate of Vertex
 * @param x x coordinate of Vertex
 * @return int distance of given Vertex
 */
int Graph::GetVertexDistance(int y, int x)
{
    pair<int, int> inputCoords;
    inputCoords.first = y;
    inputCoords.second = x;

    for (auto v : this->vertices)
    {
        if(v->coords == inputCoords)
            return v->distance;
    }
    return -999;                        // Vertex not found
}

/**
 * @brief Returns a bool indicating wheter the Graph is solvable (the start and finish are not connected, there aren't any vertices in the Graph)
 * 
 * @return true the maze is unsolvable
 * @return false the maze is solvable
 */
bool Graph::IsUnsolvable()
{
    return this->unsolvable;
}

/**
 * @brief Traverses the whole graph from the starting Vertex using breadth traversal and assigns a distance from start for each Vertex
 * 
 */
void Graph::CalculateDistance()
{
    if (this->vertices.empty() || this->start == nullptr || this->finish == nullptr)
    {
        unsolvable = true;
        return;
    }

    queue<Vertex*> foundVertices;
    this->start->distance = 0;
    foundVertices.push(this->start);

    while (!foundVertices.empty())
    {
        Vertex* currentVertex = foundVertices.front();
        foundVertices.pop();
        currentVertex->color = Color::PROCESSED;

        for (auto neighbor : currentVertex->neighbors)
        {
            if (neighbor->color == Color::UNKNOWN && (neighbor->distance == 0 || neighbor->distance == -3))
            {
                foundVertices.push(neighbor);
                neighbor->color = Color::FOUND;
                neighbor->distance = currentVertex->distance + 1;
            }
        }
    }

    if (this->finish->distance == -3)
        unsolvable = true;

    this->finish->distance = -3;
    this->start->distance = -2;
}

/**
 * @brief Selects a neighbor of finishing Vertex which is closest to the starting Vertex and calls a recursive InnerFindPath function on it
 * 
 */
void Graph::FindPath()
{
    if (this->finish->neighbors.size() == 0) 
        return;
    if (unsolvable)
        return;

    Vertex* lowestDistNeighbor = this->finish->neighbors[0];
    for (auto neighbor : finish->neighbors)
    {
        if (neighbor->distance <= lowestDistNeighbor->distance)
            lowestDistNeighbor = neighbor;
    }

    lowestDistNeighbor->InnerFindPath();

    this->start->distance = -2;
}

/**
 * @brief Destroys the Graph object
 * 
 */
Graph::~Graph()
{
    for (auto vertex : this->vertices)
    {
        delete vertex;
    }
}