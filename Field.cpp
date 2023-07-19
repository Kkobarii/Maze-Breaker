#include "Graph.h"
#include "Field.h"

/**
 * @brief Reads an input file and constructs a new Field object from it
 * 
 * @param filename input file name
 */
Field::Field(string filename)
{
    fstream file;

    file.open(filename,ios::in);
    if (!file.is_open())
    {
        cout << "File " << filename << " not found" << endl;
        return;
    }

    file >> this->rows >> this->cols;

    char squareValue;
    for (int row = 0; row < this->rows; row++)
    {
        vector<Square> tempRow;
        for (int col = 0; col < this->cols; col++)
        {
            file >> squareValue;
            squareValue -= '0';

            Square tempSquare{(int) squareValue, squareValue == 1 ? -1 : 0};

            tempRow.push_back(tempSquare);
        }
        this->squares.push_back(tempRow);
    }

    file.close();
}

/**
 * @brief Constructs a new Graph object by inserting vertices and finding their neighbors
 * 
 * @param graph empty Graph object
 */
void Field::CreateGraph(Graph * graph)
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if(this->squares[row][col].value == 1)                  // ignore walls
                continue;

            vector<pair<int, int>> neighbors;

            if (row != 0)
            {
                if (this->squares[row-1][col].value != 1)           // neighbor above
                {
                    neighbors.push_back(make_pair(row-1, col));
                }
            }
            if (row != this->rows-1)
            {
                if (this->squares[row+1][col].value != 1)           // neighbor below
                {
                    neighbors.push_back(make_pair(row+1, col));
                }
            }
            if (col != 0)
            {
                if (this->squares[row][col-1].value != 1)           // neighbor left
                {
                    neighbors.push_back(make_pair(row, col-1));
                }
            }
            if (col != this->cols-1)
            {
                if (this->squares[row][col+1].value != 1)           // neighbor right
                {
                    neighbors.push_back(make_pair(row, col+1));
                }
            }

            int dist = 0;
            if(this->squares[row][col].value == 2)
                dist = -2;
            if(this->squares[row][col].value == 3)
                dist = -3;

            graph->Insert(row, col, neighbors, dist);
        }
    }
}

/**
 * @brief Updates the Field squares distances with new distances from Graph object
 * 
 * @param graph processed Graph object with set distances 
 */
void Field::UpdateFieldDistances(Graph * graph)
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if (this->squares[row][col].value == 1)
                continue;

            this->squares[row][col].distance = graph->GetVertexDistance(row, col);
        }
    }
}

/**
 * @brief Updated the Field squares values based on squares distances
 * 
 */
void Field::UpdateFieldValues()
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if (this->squares[row][col].distance == 0)
                this->squares[row][col].value = 4;
        }
    }
}

/**
 * @brief Prints the Field squares values into the console
 * 
 */
void Field::PrintValue()
{
    cout << this->rows  << endl << this->cols << endl;

    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            cout << this->squares[row][col].value << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Prints the Field squares values into the console with style
 * 
 */
void Field::PrintValueColored()
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if (this->squares[row][col].value == 1)
            {
                cout << "■";
            }
            if (this->squares[row][col].value == 2)
            {
                cout << RED << "S" << RESET;
            }
            if (this->squares[row][col].value == 3)
            {
                cout << BLUE << "F" << RESET;
            }
            if (this->squares[row][col].value == 4)
            {
                cout << GREEN << "▫" << RESET;
            }
            if (this->squares[row][col].value == 0)
            {
                cout << " ";
            }
            cout << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Prints the Field squares distances into the console
 * 
 */
void Field::PrintDistance()
{
    cout << this->rows  << endl << this->cols << endl;

    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if (this->squares[row][col].distance >= 0 && this->squares[row][col].distance < 10)
                cout << " ";
            if(this->squares[row][col].distance < 100 && this->squares[row][col].distance > -10)
                cout << " ";

            if (this->squares[row][col].distance == -1)
            {
                cout << RED << this->squares[row][col].distance << RESET << " ";
            }
            else
            {
            cout << this->squares[row][col].distance << " ";
            }
        }
        cout << endl;
    }
}

/**
 * @brief Saves the Field squares values into an output file
 * 
 * @param filename output file name
 */
void Field::SaveFile(string filename)
{
    fstream file;

    file.open(filename,ios::out);
    if (!file.is_open())
    {
        cout << "Couldn't create a new file " << filename << endl;
        return;
    }

    file << this->rows << endl << this->cols << endl;

    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            file << (this->squares[row][col].value);
        }
        file << endl;
    }

    file.close();
}