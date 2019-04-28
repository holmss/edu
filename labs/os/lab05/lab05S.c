#include "Arr.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int max = 50;
    int * array = (int*)malloc(sizeof(int)*max);

    array = add(array, 112233, 0);
    printf("%d ", array[0]);
    array = add(array, 1208, 1);
    printf("%d\n", array[1]);
    printf("1208: %d\n", Search(array, 1208));
    Clear(array);

    return 0;
}