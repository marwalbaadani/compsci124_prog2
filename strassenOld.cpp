#include <iostream>
#include <fstream>

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

Matrix strassen(Matrix m1, Matrix m2);

Matrix naive(Matrix m1, Matrix m2);

Matrix add(Matrix m1, Matrix m2);

Matrix subtract(Matrix m1, Matrix m2);

int main(int argc, char **argv)
{

    int flag = atoi(argv[1]);
    int dimension = atoi(argv[2]);
    char *file = argv[3];
    int n;

    Matrix matrix1 = Matrix(dimension);
    Matrix matrix2 = Matrix(dimension);

    // Matrix 1 and 2 creation
    for (int i = 0; i < matrix1.size; i++)
    {
        for (int j = 0; j < matrix1.size; j++)
        {
            matrix2.array[i][j] = i * j + 1;
            matrix1.array[i][j] = i + j + 1;
        }
    }

    // Printing Matrix 1
    cout << "Matrix 1" << endl;
    for (int i = 0; i < matrix1.size; i++)
    {
        for (int j = 0; j < matrix1.size; j++)
        {
            cout << matrix1.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Printing Matrix 2
    cout << "Matrix 2" << endl;
    for (int i = 0; i < matrix1.size; i++)
    {
        for (int j = 0; j < matrix1.size; j++)
        {
            cout << matrix2.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    Matrix matrix3 = naive(matrix1, matrix2);
    Matrix matrix4 = strassen(matrix1, matrix2);

    // Printing Naive Matrix Multiplication Solution
    cout << "Naive Matrix Multiplication Solution" << endl;
    for (int i = 0; i < matrix3.size; i++)
    {
        for (int j = 0; j < matrix3.size; j++)
        {
            cout << matrix3.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // Printing Strassen Matrix Multiplication Solution
    cout << "Strassem Matrix Multiplication Solution" << endl;
    for (int i = 0; i < matrix4.size; i++)
    {
        for (int j = 0; j < matrix4.size; j++)
        {
            cout << matrix4.array[i][j] << " ";
        }
        cout << endl;
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

    // Printing out quadrants for A - G
    cout << "Quadrant A Matrix 1" << endl;
    for (int i = 0; i < a.size; i++)
    {
        for (int j = 0; j < a.size; j++)
        {
            cout << a.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Quadrant B Matrix 1" << endl;
    for (int i = 0; i < b.size; i++)
    {
        for (int j = 0; j < b.size; j++)
        {
            cout << b.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Quadrant C Matrix 1" << endl;
    for (int i = 0; i < c.size; i++)
    {
        for (int j = 0; j < c.size; j++)
        {
            cout << c.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Quadrant D Matrix 1" << endl;
    for (int i = 0; i < d.size; i++)
    {
        for (int j = 0; j < d.size; j++)
        {
            cout << d.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Quadrant E Matrix 2" << endl;
    for (int i = 0; i < e.size; i++)
    {
        for (int j = 0; j < e.size; j++)
        {
            cout << e.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;   

    cout << "Quadrant F Matrix 2" << endl;
    for (int i = 0; i < f.size; i++)
    {
        for (int j = 0; j < f.size; j++)
        {
            cout << f.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl; 

    cout << "Quadrant G Matrix 2" << endl;
    for (int i = 0; i < g.size; i++)
    {
        for (int j = 0; j < g.size; j++)
        {
            cout << g.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Quadrant H Matrix 2" << endl;
    for (int i = 0; i < h.size; i++)
    {
        for (int j = 0; j < h.size; j++)
        {
            cout << h.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

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
    cout << "S1 Matrix" << endl;
    for (int i = 0; i < s1.size; i++)
    {
        for (int j = 0; j < s1.size; j++)
        {
            cout << s1.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s2 = strassen(add(a, d), add(e, h));
    cout << "S2 Matrix" << endl;
    for (int i = 0; i < s1.size; i++)
    {
        for (int j = 0; j < s1.size; j++)
        {
            cout << s2.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s3 = strassen(subtract(a, c), add(e, f));
    cout << "S3 Matrix" << endl;
    for (int i = 0; i < s3.size; i++)
    {
        for (int j = 0; j < s3.size; j++)
        {
            cout << s3.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s4 = strassen(add(a, b), h);
    cout << "S4 Matrix" << endl;
    for (int i = 0; i < s1.size; i++)
    {
        for (int j = 0; j < s1.size; j++)
        {
            cout << s4.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s5 = strassen(a, subtract(f, h));
    cout << "S5 Matrix" << endl;
    for (int i = 0; i < s5.size; i++)
    {
        for (int j = 0; j < s5.size; j++)
        {
            cout << s5.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s6 = strassen(d, subtract(g, e));
    cout << "S6 Matrix" << endl;
    for (int i = 0; i < s1.size; i++)
    {
        for (int j = 0; j < s1.size; j++)
        {
            cout << s6.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

    s7 = strassen(add(c, d), e);
    cout << "S7 Matrix" << endl;
    for (int i = 0; i < s7.size; i++)
    {
        for (int j = 0; j < s7.size; j++)
        {
            cout << s7.array[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;

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