#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n)
{
    *p = (int **)malloc(m * sizeof(int *));  
    if (*p == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    for (int i {0}; i < m; i++)
    {
        (*p)[i] = (int *)malloc(n * sizeof(int));
        if ((*p)[i] == NULL)
        {
            printf("Memory allocation failed for row %d!\n", i);
            exit(1);
        }
    }
}

int main(void)
{
    int **array;

    allocArray(&array, 5, 10);

    for (int j {0}; j < 5; j++)
    {
        for (k {0}; k < 10; k++)
            array[j][k] = j * 10 + k;
    }

    for (int j {0}; j < 5; j++)
    {
        for (k {0}; k < 10; k++)
            printf("%p ", (void *)&(array[j][k]));
    }

    for (int j {0}; j < 5; j++)
        free(array[j]);  
    
    free(array);
}