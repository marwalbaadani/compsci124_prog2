#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
using namespace std::chrono;
using namespace std;

struct Matrix
{
    int size;
    int **array;
    Matrix(int n)
    {
        size = n;
        array = new int *[n];
        for (int i = 0; i < n; i++)
        {
            array[i] = new int[n];
        }
    }
};

// credit to geeks for geeks
unsigned int nextPowerOf2(unsigned int n)
{
    unsigned count = 0;

    // First n in the below condition
    // is for the case where n is 0
    if (n && !(n & (n - 1)))
        return n;

    while (n != 0)
    {
        n >>= 1;
        count += 1;
    }

    return 1 << count;
}

Matrix strassen(Matrix m1, Matrix m2);

Matrix strassen2(Matrix m1, Matrix m2, int num);

Matrix naive(Matrix m1, Matrix m2);

Matrix add(Matrix m1, Matrix m2);

Matrix subtract(Matrix m1, Matrix m2);

int main(int argc, char **argv)
{
    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    char *file = argv[3];
    int n;

    n = nextPowerOf2(dimension);
    cout << "n: " << n << endl;
    Matrix matrix1 = Matrix(n);
    Matrix matrix2 = Matrix(n);

    // Matrix 1 and 2 creation
    string line;
    ifstream inFile("nums.txt");
    if (inFile.is_open())
    {
        for (int i = 0; i < matrix1.size; i++)
        {
            for (int j = 0; j < matrix1.size; j++)
            {
                if (i >= dimension || j >= dimension)
                {
                    matrix1.array[i][j] = 0;
                }
                else
                {
                    getline(inFile, line);
                    matrix1.array[i][j] = stoi(line);
                }
            }
        }
        for (int i = 0; i < matrix2.size; i++)
        {
            for (int k = 0; k < matrix2.size; k++)
            {
                if (i >= dimension || k >= dimension)
                {
                    matrix1.array[i][k] = 0;
                }
                else
                {
                    getline(inFile, line);
                    matrix2.array[i][k] = stoi(line);
                }
            }
        }
    }
    else
        cout << "Unable to open file";
    inFile.close();

    Matrix matrix3 = naive(matrix1, matrix2);
    Matrix matrix4 = strassen(matrix1, matrix2);

    for (int j = 0; j < 5; j++)
    {
        for (int i = 1; i < 20; i++)
        {
            cout << " i = " << i << endl;
            auto start = steady_clock::now();

            strassen2(matrix1, matrix2, i);
            auto end = steady_clock::now();
            auto elapsed = duration_cast<microseconds>(end - start);
            auto modified = elapsed.count();

            auto start2 = steady_clock::now();
            strassen(matrix1, matrix2);
            auto end2 = steady_clock::now();
            auto elapsed2 = duration_cast<microseconds>(end2 - start2);
            auto regular = elapsed2.count();

            if (modified > regular)
            {
                cout << "MODIFIED GREATER" << endl;
            }
            else if (modified < regular)
            {
                cout << "REGULAR GREATER" << endl;
            }
        }
        cout << endl
             << endl;
    }
    cout << "Strassen Diagonal" << endl;
    int count = 0;
    for (int i = 0; i < matrix4.size; i++)
    {
        for (int j = 0; j < matrix4.size; j++)
        {
            if (i == j && count < dimension)
            {
                cout << matrix4.array[i][j] << " ";
                count++;
            }
        }
    }
    cout << endl;
}

// Naive solution
Matrix naive(Matrix m1, Matrix m2)
{
    Matrix m3 = Matrix(m1.size);
    for (int i = 0; i < m1.size; i++)
    {
        for (int j = 0; j < m1.size; j++)
        {
            int m1p = 0;
            for (int k = 0; k < m1.size; k++)
            {
                m1p += m1.array[i][k] * m2.array[k][j];
            }
            m3.array[i][j] = m1p;
        }
    }
    return m3;
}

Matrix add(Matrix m1, Matrix m2)
{
    Matrix m3 = Matrix(m1.size);
    int size = m1.size;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            m3.array[i][j] = m1.array[i][j] + m2.array[i][j];
        }
    }
    return m3;
}

Matrix subtract(Matrix m1, Matrix m2)
{
    Matrix m3 = Matrix(m1.size);
    int size = m1.size;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {

            m3.array[i][j] = m1.array[i][j] - m2.array[i][j];
        }
    }

    return m3;
}

Matrix strassen(Matrix m1, Matrix m2)
{
    int n = m1.size;
    if (n == 1)
    {
        Matrix m3 = Matrix(1);
        m3.array[0][0] = m1.array[0][0] * m2.array[0][0];
        return m3;
    }

    Matrix a = Matrix(n / 2);
    Matrix e = Matrix(n / 2);
    Matrix b = Matrix(n / 2);
    Matrix f = Matrix(n / 2);
    Matrix c = Matrix(n / 2);
    Matrix g = Matrix(n / 2);
    Matrix d = Matrix(n / 2);
    Matrix h = Matrix(n / 2);

    // quardrant A and B for m1 and m2
    for (int rows = 0; rows < n / 2; rows++)
    {
        for (int cols = 0; cols < n / 2; cols++)
        {
            a.array[rows][cols] = m1.array[rows][cols];
            e.array[rows][cols] = m2.array[rows][cols];
        }

        for (int cols = n / 2; cols < n; cols++)
        {
            b.array[rows][cols - n / 2] = m1.array[rows][cols];
            f.array[rows][cols - n / 2] = m2.array[rows][cols];
        }
    }

    // quadrant C and D for m1 and m2
    for (int rows = n / 2; rows < n; rows++)
    {
        for (int cols = 0; cols < n / 2; cols++)
        {
            c.array[rows - n / 2][cols] = m1.array[rows][cols];
            g.array[rows - n / 2][cols] = m2.array[rows][cols];
        }

        for (int cols = n / 2; cols < n; cols++)
        {
            d.array[rows - n / 2][cols - n / 2] = m1.array[rows][cols];
            h.array[rows - n / 2][cols - n / 2] = m2.array[rows][cols];
        }
    }

    Matrix s1 = Matrix(n / 2);
    Matrix s2 = Matrix(n / 2);
    Matrix s3 = Matrix(n / 2);
    Matrix s4 = Matrix(n / 2);
    Matrix s5 = Matrix(n / 2);
    Matrix s6 = Matrix(n / 2);
    Matrix s7 = Matrix(n / 2);
    Matrix qA = Matrix(n / 2);
    Matrix qB = Matrix(n / 2);
    Matrix qC = Matrix(n / 2);
    Matrix qD = Matrix(n / 2);

    s1 = strassen(subtract(b, d), add(g, h));
    s2 = strassen(add(a, d), add(e, h));
    s3 = strassen(subtract(a, c), add(e, f));
    s4 = strassen(add(a, b), h);
    s5 = strassen(a, subtract(f, h));
    s6 = strassen(d, subtract(g, e));
    s7 = strassen(add(c, d), e);

    qA = add(subtract(add(s1, s2), s4), s6);
    qB = add(s4, s5);
    qC = add(s6, s7);
    qD = subtract(add(subtract(s2, s3), s5), s7);

    Matrix result = Matrix(n);

    // Quadrant A
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {

            result.array[i][j] = qA.array[i][j];
        }
    }

    // Quadrant B
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {

            result.array[i][j] = qB.array[i][j - n / 2];
        }
    }

    // Quadrant C
    for (int i = n / 2; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {

            result.array[i][j] = qC.array[i - n / 2][j];
        }
    }

    // quadrant D
    for (int i = n / 2; i < n; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            result.array[i][j] = qD.array[i - n / 2][j - n / 2];
        }
    }
    return result;
}

Matrix strassen2(Matrix m1, Matrix m2, int num)
{
    int n = m1.size;
    if (n == num)
    {
        return naive(m1, m2);
    }

    Matrix a = Matrix(n / 2);
    Matrix e = Matrix(n / 2);
    Matrix b = Matrix(n / 2);
    Matrix f = Matrix(n / 2);
    Matrix c = Matrix(n / 2);
    Matrix g = Matrix(n / 2);
    Matrix d = Matrix(n / 2);
    Matrix h = Matrix(n / 2);

    // quardrant A and B for m1 and m2
    for (int rows = 0; rows < n / 2; rows++)
    {
        for (int cols = 0; cols < n / 2; cols++)
        {
            a.array[rows][cols] = m1.array[rows][cols];
            e.array[rows][cols] = m2.array[rows][cols];
        }

        for (int cols = n / 2; cols < n; cols++)
        {
            b.array[rows][cols - n / 2] = m1.array[rows][cols];
            f.array[rows][cols - n / 2] = m2.array[rows][cols];
        }
    }

    // quadrant C and D for m1 and m2
    for (int rows = n / 2; rows < n; rows++)
    {
        for (int cols = 0; cols < n / 2; cols++)
        {
            c.array[rows - n / 2][cols] = m1.array[rows][cols];
            g.array[rows - n / 2][cols] = m2.array[rows][cols];
        }

        for (int cols = n / 2; cols < n; cols++)
        {
            d.array[rows - n / 2][cols - n / 2] = m1.array[rows][cols];
            h.array[rows - n / 2][cols - n / 2] = m2.array[rows][cols];
        }
    }

    Matrix s1 = Matrix(n / 2);
    Matrix s2 = Matrix(n / 2);
    Matrix s3 = Matrix(n / 2);
    Matrix s4 = Matrix(n / 2);
    Matrix s5 = Matrix(n / 2);
    Matrix s6 = Matrix(n / 2);
    Matrix s7 = Matrix(n / 2);
    Matrix qA = Matrix(n / 2);
    Matrix qB = Matrix(n / 2);
    Matrix qC = Matrix(n / 2);
    Matrix qD = Matrix(n / 2);

    s1 = strassen(subtract(b, d), add(g, h));
    s2 = strassen(add(a, d), add(e, h));
    s3 = strassen(subtract(a, c), add(e, f));
    s4 = strassen(add(a, b), h);
    s5 = strassen(a, subtract(f, h));
    s6 = strassen(d, subtract(g, e));
    s7 = strassen(add(c, d), e);

    qA = add(subtract(add(s1, s2), s4), s6);
    qB = add(s4, s5);
    qC = add(s6, s7);
    qD = subtract(add(subtract(s2, s3), s5), s7);

    Matrix result = Matrix(n);

    // Quadrant A
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {

            result.array[i][j] = qA.array[i][j];
        }
    }

    // Quadrant B
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {

            result.array[i][j] = qB.array[i][j - n / 2];
        }
    }

    // Quadrant C
    for (int i = n / 2; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {

            result.array[i][j] = qC.array[i - n / 2][j];
        }
    }

    // quadrant D
    for (int i = n / 2; i < n; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            result.array[i][j] = qD.array[i - n / 2][j - n / 2];
        }
    }
    return result;
}
