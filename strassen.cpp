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
    if (dimension % 4 != 0)
        n = dimension + (4 - dimension % 4);
    else
        n = dimension;

    cout << "\n dim:" << dimension << "\nn: " << n;
    int matrix1[n][n];
    int matrix2[n][n];
    ifstream in;
    in.open(file);
    if (!in)
    {
        printf("Couldn't access file\n");
        exit(1);
    }

    cout << " opening";
    if (in.is_open())
    {
        // for each number:
        while (in >> value)
        {
            matrix1[];
            cout << "\nValue: " << value; // Print out variable
        }
    }
    in.close();
    cout << "closing";
}
