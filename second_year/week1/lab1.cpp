#include <iostream>

void allocArray(int ***p, int m, int n)
{

}

int main(void)
{
  int **array;

  allocArray(&array, 5, 10);

  for(int j{0}; j < 5; j++)
  {
    for(int k{0}; k < 10; k++)
      array[j][k] = j * 10 + k;
  }

  for(int j{0}; j < 5; j++)
  {
    for(int k{0}; k < 10; k++)
      std::cout << array[j][k] << " ";
  }
}
