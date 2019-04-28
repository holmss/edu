#include "Arr.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main()
{
    void *library = dlopen("./libdyn.so", RTLD_LAZY);
    if (!library)
    {
        perror("dlopen");
        return 1;
    }

    int (*Get)(int *, int);
    void (*Sort)(int *);
    int (*length)(int *);
    int* (*add)(int *, int, int);
    int (*Search)(int *, int);
    void (*Clear)(int *);

    Get = dlsym(library, "Get");
    Sort = dlsym(library, "Sort");
    length = dlsym(library, "legth");
    add = dlsym(library, "add");
    Search = dlsym(library, "Search");
    Clear = dlsym(library, "Clear");

    int max = 50;
    int * array = (int*)malloc(sizeof(int)*max);

    array = add(array, 112233, 0);
    printf("%d ", array[0]);
    array = add(array, 1208, 1);
    printf("%d\n", array[1]);
    printf("1208: %d\n", Search(array, 1208));
    Clear(array);

    dlclose(library);

    return 0;
}