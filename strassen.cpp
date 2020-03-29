#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
    // declare variables
    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    char *file = argv[3];
    int n;
    int value;

    // decide when to pad with zeroes
    if (dimension % 2 != 0)
        n = dimension + (2 - dimension % 2);
    else
        n = dimension;

    int matrix1[4][4] = {{1, 2, 3, 4},
                         {4, 3, 2, 1},
                         {5, 6, 7, 8},
                         {8, 7, 6, 5}};
    int matrix2[4][4] = {{4, 3, 2, 1},
                         {1, 2, 3, 4},
                         {8, 7, 6, 5},
                         {5, 6, 7, 8}};
    int matrix3[n][n];

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            int m1p = 0;
            for (int k = 0; k < dimension; k++)
            {
                m1p += matrix1[i][k] * matrix2[k][j];
            }
            // cout << m1p << "  \t";
            matrix3[i][j] = m1p;
            cout << matrix3[i][j] << " \t";
        }
        cout << "\n";
    }

    ifstream in;
    in.open(file);
    if (!in)
    {
        printf("Couldn't access file\n");
        exit(1);
    }

    if (in.is_open())
    {
        // for each number:
        while (in >> value)
        {
            // matrix1[][];
            // cout << "\nValue: " << value; // Print out variable
        }
    }
    in.close();

    cout << "closing\n";
}

int **multiply(int *a, int *b)
{
    int **c;

    return c;
}