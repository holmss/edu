#include <stdio.h>
#include <stdlib.h>
#include "Arr.h"

#define IERR 1

int Get(int * arr, int i)
{   
    if(i < 0 || i > length(arr))
        return IERR;

    return arr[i];
}

void Sort(int * arr)
{
    int i, j;
    int tmp;

    for (i = 1; i < length(arr); i++)
    {
        for(j = i + 1; j < length(arr); j++)
        {
            if(arr[j] < arr[j - 1])
            {
                tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp; 
            }
        }
    }
}

int length(int * arr)
{
    return sizeof(arr)/sizeof(int);
}

int * add (int * arr, int element, int index)
{
    if(index < 0 || index > length(arr))
        return (int*)IERR;

    arr[index] = element;
    return arr;
}

int Search(int * arr, int value)
{
    int i;
    for(i = 0; i < length(arr); i++)
        if(arr[i] == value)
            return i;
}

void Clear(int * arr)
{
    int i;
    for (i = 0; i < length(arr); i++)
        arr[i] = 0;
}
