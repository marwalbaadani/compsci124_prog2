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

    for (int i = 0; i < matrix1.size; i++)
    {
        for (int j = 0; j < matrix1.size; j++)
        {
            matrix1.array[i][j] = 7;
            matrix2.array[i][j] = 3;
        }
    }

    Matrix matrix3 = naive(matrix1, matrix2);
    Matrix matrix4 = strassen(matrix1, matrix2);

    for (int i = 0; i < matrix3.size; i++)
    {
        for (int j = 0; j < matrix3.size; j++)
        {
            cout << matrix3.array[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < matrix4.size; i++)
    {
        for (int j = 0; j < matrix4.size; j++)
        {
            cout << matrix4.array[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix naive(Matrix m1, Matrix m2)
{

    Matrix m3 = Matrix(m1.size);
    for (int i = 0; i < m1.size; i++) //naive method
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

    // quadrant 2
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            a.array[i][j] = m1.array[i][j];
            e.array[i][j] = m2.array[i][j];
        }
    }

    // quadrant 1
    for (int i = n / 2; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            b.array[i][j] = m1.array[i][j];
            f.array[i][j] = m2.array[i][j];
        }
    }

    // quadrant 3
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            c.array[i][j] = m1.array[i][j];
            g.array[i][j] = m2.array[i][j];
        }
    }
    // quadrant 4
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            d.array[i][j] = m1.array[i][j];
            h.array[i][j] = m2.array[i][j];
        }
    }

    Matrix s1 = Matrix(n / 2);
    Matrix s2 = Matrix(n / 2);
    Matrix s3 = Matrix(n / 2);
    Matrix s4 = Matrix(n / 2);
    Matrix s5 = Matrix(n / 2);
    Matrix s6 = Matrix(n / 2);
    Matrix s7 = Matrix(n / 2);
    Matrix q2 = Matrix(n / 2);
    Matrix q1 = Matrix(n / 2);
    Matrix q3 = Matrix(n / 2);
    Matrix q4 = Matrix(n / 2);

    s1 = strassen(subtract(b, d), add(g, h));
    cout << "checkpoint 1" << endl;
    cout << n << endl;
    s2 = strassen(add(a, d), add(e, h));
    s3 = strassen(subtract(a, c), add(e, f));
    s4 = strassen(subtract(a, b), h);
    s5 = strassen(a, add(f, h));
    s6 = strassen(d, subtract(g, e));
    s7 = strassen(add(c, d), e);

    q2 = add(subtract(add(s1, s2), s4), s6);
    q1 = subtract(s4, s5);
    q3 = add(s6, s7);
    q4 = subtract(add(subtract(s2, s3), s5), s7);

    Matrix result = Matrix(n / 2);
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            result.array[i][j] = q2.array[i][j];
        }
    }

    // quadrant 1
    for (int i = n / 2; i < n; i++)
    {
        for (int j = 0; j < n / 2; j++)
        {
            result.array[i][j] = q1.array[i][j];
        }
    }

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            result.array[i][j] = q3.array[i][j];
        }
    }
    // quadrant 4
    for (int i = 0; i < n / 2; i++)
    {
        for (int j = n / 2; j < n; j++)
        {
            result.array[i][j] = q4.array[i][j];
        }
    }
    return result;
}