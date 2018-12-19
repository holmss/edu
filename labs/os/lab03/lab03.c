#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>
#include <pthread.h>

#define NUM_OF_THREADS 100
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD   -12
#define SUCCESS        0
#define CYCLE          1

//6 вариант
/* Провести распараллеленный поиск по ненаправленному графу в ширину.
Граф задается набором значений, что хранятся в вершинах, и набором пар связей.
Информация по графу хранится в отдельнм файле. 
Необходимо определить, есть ли в графе циклы */


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int cycle = 0;

typedef struct TVertex
{
    int value;
    int used;
} Vertex;

typedef struct TNode
{
    Vertex * value;
    struct TNode * next;
} Node;

typedef struct TQueue
{
    Node * head;
    Node * tail;
} Queue;

typedef struct TPare
{
    Vertex first, second;
} Pare;

typedef struct TGraph
{
    int el_num;
    Vertex *g_elems;
    Pare *g_links;
    Vertex **adj_matrix;
} Graph;

typedef struct TArgs
{
    int iind, jind;
    Vertex ** adj_matrix;
} Args;

Queue* Push(Queue* queue, int value)
{
   Node* node = malloc(sizeof(Node));
   node->value = value;
   node->next = NULL;
 
   if (queue->head && queue->tail)
   {
      queue->tail->next = node;
      queue->tail = node;
   }
   else
   {
      queue->head = queue->tail = node;
   }
 
   return queue;
}

int Pop(Queue* queue)
{
   int value = 0;
 
   if (queue->head)
   {
      value = queue->head->value;
      queue->head = queue->head->next;
   }
 
   return value;
}

void Clear(Queue* queue)
{
    while (queue->head)
    {
        Pop(queue);
    }
 
    queue->head = queue->tail = NULL;
}

void Print(const Queue* queue)
{
   const Node* node = queue->head;
 
   for (; node; node = node->next)
   {
      printf("%d ", node->value);
   }
   printf("\n");
}

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
        if (((arr[i].first.value == p.first.value) && (arr[i].second.value == p.second.value)) ||
            ((arr[i].first.value == p.second.value) && (arr[i].second.value == p.first.value)))
            return 0;
    }
    return 1;
}

void* ByPassWide(void* args)
{
    // Args * params = (Args *) args;
    
    // if (params.adj_matrix[iind][jind].used == 0)
    // {
    //     pthread_mutex_lock(&lock);
    //     pthread_t temp_thread;
    //     params.adj_matrix[iind][jind].used = 1;
    //     params.adj_matrix[jind][iind].used = 1;

    //     params.iind = params.jind;
    //     params.jind = 0;
    //     pthread_create(temp_thread, NULL, ByPassWide, params);

    // }

    return SUCCESS;
}

int main()
{
    int i = 0;
    int _max_count;

    Graph graph;
    Pare pare;

    printf("Enter the number of elements of graph:\n");
    scanf("%d", &graph.el_num);

    _max_count = graph.el_num;
    graph.g_elems = (Vertex *)malloc(sizeof(Vertex) * graph.el_num);

    while (i < graph.el_num)
    {
        printf("Enter %d element:\n", i + 1);
        scanf("%d", &graph.g_elems[i].value);
        ++i;
    }

    int max_links = factorial(graph.el_num);
    graph.g_links = (Pare *)malloc(sizeof(Pare) * max_links);

    for(i = 0; i < max_links; i++)
    {
        graph.g_links[i].first.value = graph.g_links[i].second.value = 0;
    }

    for (i = 0; i < max_links && getchar() != EOF;)
    {
        printf ("Enter next link:\n");
        scanf("%d%d", &pare.first.value, &pare.second.value);
        if (pare.first.value <= graph.el_num && pare.second.value <= graph.el_num && pare.first.value != pare.second.value)
            if (CheckPare(pare, graph.g_links, i + 1) == 1)
            {
                graph.g_links[i].first.value = pare.first.value;
                graph.g_links[i].second.value = pare.second.value;
                ++i;
            }
    }

    max_links = i;

    graph.adj_matrix = 0;
    graph.adj_matrix = (Vertex **)malloc(sizeof(Vertex *) * graph.el_num);
    printf("%d \n", graph.el_num);
    for(i = 0; i < graph.el_num; ++i)
    {
        graph.adj_matrix[i] = (Vertex *)malloc(sizeof(Vertex) * graph.el_num);
    }

    int j;
    for(i = 0; i < graph.el_num; i++)
        for(j = 0; j < graph.el_num; j++)
            graph.adj_matrix[i][j].value = 0;

    for (i = 0; i < max_links; i++)
    {
        graph.adj_matrix[graph.g_links[i].first.value - 1][graph.g_links[i].second.value - 1].value = 1;
        graph.adj_matrix[graph.g_links[i].second.value - 1][graph.g_links[i].first.value - 1].value = 1;
    }

    for(i = 0; i < graph.el_num; i++)
    {
        for(j = 0; j < graph.el_num; j++)
            printf("%d ", graph.adj_matrix[i][j].value);
        putchar('\n');
    }

    pthread_t threads[NUM_OF_THREADS];
    int status;
    int status_addr; 

    // for (i = 0; i < _max_count; ++i)
    // {
    //     for (j = 0; j < _max_count; ++j)
    //     {
    //         if (graph.adj_matrix[i][j].value == 1)
    //         {
    //             Args params;
    //             params.iind = i;
    //             params.jind = j;
    //             params.adj_matrix = graph.adj_matrix;

    //             status = pthread_create(&threads[i], NULL, ByPassWide, (void*)&params);
    //         }

    //     }
    // }
    
    for (i = 0; i < _max_count; ++i)
        

    if (status != 0) {
        printf("pthread_create error\n");
        exit(ERROR_CREATE_THREAD);
    }

    for (i = 0; j < NUM_OF_THREADS; ++j) {
        pthread_join(threads[j], NULL); 
    }

    printf("There are no cycles in that graph");

    for(i = 0; i < graph.el_num; i++)
    {
        free(graph.adj_matrix[i]);
    }

    free(graph.adj_matrix);
    free(graph.g_elems);
    free(graph.g_links);

    pthread_mutex_destroy(&lock);

    return 0;
}