#include "Include/Graph.h"
#include "Include/Field.h"
#include "Include/Maze.h"

/**
 * @brief Reads a Maze from an input file, solves it and saves it into an output file
 * 
 * @param inputFile input file name
 * @param outputFile output file name
 * @param print bool specifying whether to print the solved maze into the console or not
 */
void Maze::Solve(string inputFile, string outputFile, bool print)
{
    field = new Field(inputFile);
    graph = new Graph();
    field->CreateGraph(graph);

    graph->CalculateDistance();

    if (graph->IsUnsolvable())
    {
        if (print)
        {
            field->PrintValueColored();
            cout << "This maze is unsolvable." << endl << endl;
        }

        delete graph;
        delete field;
        return;
    }

    graph->FindPath();

    field->UpdateFieldDistances(graph);
    field->UpdateFieldValues();

    if (print)
    {
        field->PrintValueColored();
        cout << endl;
    }

    field->SaveFile(outputFile);

    delete graph;
    delete field;
}

/**
 * @brief Reads a Maze from an input file, solves it and saves it into an output file, while also printing debug information into the console 
 * 
 * @param inputFile input file name
 * @param outputFile output file name
 */
void Maze::SolveDebug(string inputFile, string outputFile)
{
    field = new Field(inputFile);
    graph = new Graph();
    field->CreateGraph(graph);

    field->UpdateFieldDistances(graph);
    field->PrintDistance();

    graph->CalculateDistance();

    field->UpdateFieldDistances(graph);
    field->PrintDistance();

    cout << "unsolvable? " << (graph->IsUnsolvable() ? "yes" : "no") << endl;

    if (graph->IsUnsolvable())
    {
        field->PrintValueColored();
        cout << "This maze is unsolvable." << endl << endl;

        delete graph;
        delete field;
        return;
    }

    graph->FindPath();

    field->UpdateFieldDistances(graph);
    field->PrintDistance();

    field->UpdateFieldValues();
    field->PrintValueColored();
    cout << endl;

    field->SaveFile(outputFile);

    delete graph;
    delete field;
}