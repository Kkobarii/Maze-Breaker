#ifndef maze_h
    #define maze_h

#include "includes.h"
#include "Graph.h"
#include "Field.h"

/**
 * @brief Class containing a Field and a Graph and also methods for solving the Maze
 * 
 */
class Maze
{
private:
    Field * field;
    Graph * graph;

public:
    void Solve(string inputFile, string outputFile, bool print);
    void SolveDebug(string inputFile, string outputFile);
};

#endif