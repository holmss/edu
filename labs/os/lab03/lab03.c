#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0

//6 вариант
/* Провести распараллеленный поиск по ненаправленному графу в ширину.
Граф задается набором значений, что хранятся в вершинах, и набором пар связей.
Информация по графу хранится в отдельнм файле. 
Необходимо определить, есть ли в графе циклы */

typedef struct TPare
{
    int first, second;
} Pare;

typedef struct TGraph
{
    int el_num;
    int *g_elems;
    Pare *g_links;
    int **adj_matrix;
} Graph;

int factorial(int n)
{
    if (n == 2)
    {
        return n;
    }
    return n * factorial(n - 1);
}

int CheckPare(Pare p, Pare *arr, int arr_size)
{
    int i = 0;
    for (i = 0; i < arr_size; i++)
    {
        if (((arr[i].first == p.first) && (arr[i].second == p.second)) ||
            ((arr[i].first == p.second) && (arr[i].second == p.first)))
            return 0;
    }
    return 1;
}

void* ByPassWide(void* args)
{
    
    return SUCCESS; //успехов
}

int main()
{
    int i = 0;

    Graph graph;
    Pare pare;

    printf("Enter the number of elements of graph:\n");
    scanf("%d", &graph.el_num);

    graph.g_elems = (int *)malloc(sizeof(int) * graph.el_num);

    while (i < graph.el_num)
    {
        printf("Enter %d element:\n", i + 1);
        scanf("%d", &graph.g_elems[i]);
        ++i;
    }

    int max_links = factorial(graph.el_num);
    graph.g_links = (Pare *)malloc(sizeof(Pare) * max_links);

    for(i = 0; i < max_links; i++)
    {
        graph.g_links[i].first = graph.g_links[i].second = 0;
    }

    for (i = 0; i < max_links && getchar() != EOF;)
    {
        printf ("Enter next link:\n");
        scanf("%d%d", &pare.first, &pare.second);
        if (pare.first <= graph.el_num && pare.second <= graph.el_num && pare.first != pare.second)
            if (CheckPare(pare, graph.g_links, i + 1) == 1)
            {
                graph.g_links[i].first = pare.first;
                graph.g_links[i].second = pare.second;
                ++i;
            }
    }

    max_links = i;

    graph.adj_matrix = 0;
    graph.adj_matrix = (int **)malloc(sizeof(int *) * graph.el_num);
    printf("%d \n", graph.el_num);
    for(i = 0; i < graph.el_num; ++i)
    {
        graph.adj_matrix[i] = (int*)malloc(sizeof(int) * graph.el_num);
    }

    int j;
    for(i = 0; i < graph.el_num; i++)
        for(j = 0; j < graph.el_num; j++)
            graph.adj_matrix[i][j] = 0;

    for (i = 0; i < max_links; i++)
    {
        graph.adj_matrix[graph.g_links[i].first - 1][graph.g_links[i].second - 1] = 1;
        graph.adj_matrix[graph.g_links[i].second - 1][graph.g_links[i].first - 1] = 1;
    }

    for(i = 0; i < graph.el_num; i++)
    {
        for(j = 0; j < graph.el_num; j++)
            printf("%d ", graph.adj_matrix[i][j]);
        putchar('\n');
    }

    pthread_t thread;
    pthread_mutex_t lock;
    int status;
    int status_addr; 

    status =  pthread_create(&thread, NULL, ByPassWide, (void*)graph);
    
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
        exit(ERROR_CREATE_THREAD);
    }



    for(i = 0; i < graph.el_num; i++)
    {
        free(graph.adj_matrix[i]);
    }

    free(graph.adj_matrix);

    free(graph.g_elems);
    free(graph.g_links);

    return 0;
}