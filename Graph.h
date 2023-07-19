#ifndef graph_h
    #define graph_h

#include "includes.h"

/**
 * @brief Color enum used in breadth traversal of Graph
 * 
 */
enum Color {UNKNOWN, FOUND, PROCESSED};

/**
 * @brief Maze represented as a Graph - list of Vertices connected together. Used for finding the way through the Maze
 * 
 */
class Graph
{
private:
    class Vertex
    {
    public:
        pair<int, int> coords;
        vector<Vertex*> neighbors;
        int distance;   // 0 = unknown, -1 = wall, -2 = start, -3 = finish
        int color = Color::UNKNOWN;  // 0 = unknown, 1 = found, 2 = processed

        /**
         * @brief Constructs a new Vertex object
         * 
         * @param y y coordinate of Vertex
         * @param x x coordinate of Vertex
         * @param distance distance from the start
         */
        Vertex (int y, int x, int distance)
        {
            this->coords.first = y;
            this->coords.second = x;
            this->distance = distance;
        }

        /**
         * @brief Recursively traverses the Graph, calling itself on the neighboring Vertex which has a distance smaller by one, to find the path back to the start
         * 
         */
        void InnerFindPath()
        {
            for (auto v : this->neighbors)
            {
                if (v->distance == this->distance - 1 && v->distance > 0)
                {
                    v->InnerFindPath();
                    break;                  // to make sure only one path is created - the first one
                }
            }
            this->distance = 0;
        }
    };

    vector<Vertex*> vertices;

    Vertex* start;
    Vertex* finish;

    bool unsolvable = false;

public:
    void Insert(int y, int x, vector<pair<int, int>> neigbors, int distance);
    void Print();

    int GetVertexDistance(int y, int x);
    bool IsUnsolvable();

    void CalculateDistance();
    void FindPath();
    ~Graph();
};

#endif