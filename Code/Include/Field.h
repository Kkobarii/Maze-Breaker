#ifndef field_h
    #define field_h

#include "includes.h"
#include "Graph.h"

/**
 * @brief Structure containing information about a tile in the Maze
 * 
 */
typedef struct
{
    int value;
    int distance;
} Square;

/**
 * @brief Maze represented as a Field - a 2D matrix of Square coresponding with the input and output file format. Used for reading and writing the Maze
 * 
 */
class Field
{
private:
    int rows;
    int cols;
    vector<vector<Square>> squares;

public:
    Field(string filename);

    void CreateGraph(Graph * graph);
    void UpdateFieldDistances(Graph * graph);
    void UpdateFieldValues();

    void PrintValue();
    void PrintValueColored();
    void PrintDistance();

    void SaveFile(string filename);
};

#endif