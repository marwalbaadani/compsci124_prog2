#include <iostream>
#include <fstream>
using namespace std;

int **operation(int **m, int **n, int size, int op)
{
    int **r;
    // or int **r; ?
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (op == 0)
            {
                r[i][j] = m[i][j] - n[i][j];
            }
            else if (op == 1)
            {
                r[i][j] = m[i][j] + n[i][j];
            }
        }
    }
    return r;
}
// strassen takes two 2-d arrays, returns 2-d array
int **strassen(int **m, int **n)
{

    int rows = sizeof(m) / sizeof(m[0]);
    cout << rows;
    int cols = sizeof(m[0]) / sizeof(m[0][0]);

    int **a;
    int **e;
    int **b;
    int **f;
    int **c;
    int **g;
    int **d;
    int **h;
    // quadrant 2
    for (int i = 0; i < rows / 2; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            a[i][j] = m[i][j];
            e[i][j] = n[i][j];
        }
    }
    // quadrant 1
    for (int i = cols / 2; i < cols; i++)
    {
        for (int j = 0; j < rows / 2; j++)
        {
            b[i][j] = m[i][j];
            f[i][j] = n[i][j];
        }
    }
    // quadrant 3
    for (int i = 0; i < cols / 2; i++)
    {
        for (int j = rows / 2; j < rows; j++)
        {
            c[i][j] = m[i][j];
            g[i][j] = n[i][j];
        }
    }
    // quadrant 4
    for (int i = 0; i < cols / 2; i++)
    {
        for (int j = rows / 2; j < rows; j++)
        {
            d[i][j] = m[i][j];
            h[i][j] = n[i][j];
        }
    }
    int **s1 = strassen(operation(b, d, rows, 0), operation(g, h, rows, 1));
    int **s2 = strassen(operation(a, d, rows, 1), operation(e, h, rows, 1));
    int **s3 = strassen(operation(a, c, rows, 0), operation(e, f, rows, 1));
    int **s4 = strassen(operation(a, b, rows, 0), h);
    int **s5 = strassen(a, operation(f, h, rows, 1));
    int **s6 = strassen(d, operation(g, e, rows, 0));
    int **s7 = strassen(operation(c, d, rows, 1), e);

    int **q2 = operation(operation(operation(s1, s2, rows, 1), s4, rows, 0), s6, rows, 1);
    int **q1 = operation(s4, s5, rows, 0);
    int **q3 = operation(s6, s7, rows, 1);
    int **q4 = operation(operation(operation(s2, s3, rows, 0), s5, rows, 1), s7, rows, 0);
    int **r;
    // quadrant 2
    for (int i = 0; i < rows / 2; i++)
    {
        for (int j = 0; j < cols / 2; j++)
        {
            r[i][j] = q2[i][j];
        }
    }

    // quadrant 1
    for (int i = cols / 2; i < cols; i++)
    {
        for (int j = 0; j < rows / 2; j++)
        {
            r[i][j] = q1[i][j];
        }
    }

    for (int i = 0; i < cols / 2; i++)
    {
        for (int j = rows / 2; j < rows; j++)
        {
            r[i][j] = q3[i][j];
        }
    }
    // quadrant 4
    for (int i = 0; i < cols / 2; i++)
    {
        for (int j = rows / 2; j < rows; j++)
        {
            r[i][j] = q4[i][j];
        }
    }

    return r;
}

int main(int argc, char **argv)
{
    // declare variables
    cout << "checkpoint 0" << endl;
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

    cout << "checkpoint 1" << endl;

    int **matrix1 = new int *[dimension];
    int **matrix2 = new int *[dimension];

    for (int i = 0; i < dimension; i++)
    {
        matrix1[i] = new int[dimension];
        matrix2[i] = new int[dimension];
    }
    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << "checkpoint 1.5" << endl;
            matrix1[i][j] = 2;
            matrix2[i][j] = 3;
        }
    }
    cout << "checkpoint 2" << endl;

    int **m3 = strassen(matrix1, matrix2);

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            cout << m3[i][j];
        }
    }
    int matrix3[n][n];
    // for (int i = 0; i < dimension; i++) //naive method
    // {
    //     for (int j = 0; j < dimension; j++)
    //     {
    //         int m1p = 0;
    //         for (int k = 0; k < dimension; k++)
    //         {
    //             m1p += matrix1[i][k] * matrix2[k][j];
    //         }
    //         // cout << m1p << "  \t";
    //         matrix3[i][j] = m1p;
    //         cout << matrix3[i][j] << " \t";
    //     }
    //     cout << "\n";
    // }

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

// how to find dimensions of 2d array
// int rows = sizeof(arr)/sizeof(arr[0]);
// int cols = sizeof(arr[0])/sizeof(arr[0][0]);