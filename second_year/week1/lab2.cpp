#include <iostream>

template<class T>
class Memory
{
public:
    static T **allocArray(int m, int n)
    {
        T **p = new T*[m];
        for (int i{0}; i < m; i++)
            p[i] = new T[n];

        return p;
    }
};

void freeArray(int **p, int rows)
{
    for (int i = 0; i < rows; i++)
        delete[] p[i];

    delete[] p;
}

int main(void)
{
    int **array = Memory<int>::allocArray(5, 10);

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 10; k++)
            array[j][k] = j * 10 + k;
    }

    for (int j = 0; j < 5; j++)
    {
        for (int k = 0; k < 10; k++)
            std::cout << array[j][k] << " ";
    }

    freeArray(array, 5);
}
