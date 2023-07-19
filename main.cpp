/**
 * @file main.cpp
 * @author Kkobari
 * @brief 
 * @version 0.1
 * @date 2022-05-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "includes.h"
#include "Graph.h"
#include "Field.h"
#include "Maze.h"

int main (void)
{
    cout << endl;
    bool print = true;

    Maze maze;
    for (int i = 0; i < 12; i++)
    {
        string maze_name = "./Data/bludiste_" + std::to_string(i) + ".txt"; 
        maze.Solve(maze_name, "./Data/output.txt", print);
    }

    maze.SolveDebug("./Data/bludiste_2.txt", "./Data/output.txt");
    maze.SolveDebug("./Data/bludiste_3.txt", "./Data/output.txt");

    return 0;
}