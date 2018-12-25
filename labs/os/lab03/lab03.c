#include <malloc.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_OF_THREADS 100
#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD -12
#define SUCCESS 0
#define CYCLE 1

//6 вариант
/* Провести распараллеленный поиск по ненаправленному графу в ширину.
Граф задается набором значений, что хранятся в вершинах, и набором пар связей.
Информация по графу хранится в отдельнм файле. 
Необходимо определить, есть ли в графе циклы */

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int cycle = 0;

typedef struct TVertex {
    int num;
    int value;
    int used;
} Vertex;

typedef struct TNode {
    Vertex* value;
    struct TNode* next;
} Node;

typedef struct TQueue {
    Node* head;
    Node* tail;
    int len;
} Queue;

typedef struct TPare {
    Vertex first, second;
} Pare;

typedef struct TGraph {
    int el_num;
    Vertex* g_elems;
    Pare* g_links;
    int** adj_matrix;
} Graph;

typedef struct TArgs {
    Queue* q;
    Graph g;
    int i;
} Args;

Queue* Create()
{
    Queue* res = (Queue*)malloc(sizeof(Queue));
    res->head = (Node*)malloc(sizeof(Node));
    res->tail = NULL;
    res->len = 0;
    return res;
}

Queue* Push(Queue* queue, Vertex* value)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    if (!queue->tail) {
        queue->tail = queue->head = node;
        return queue;
    }

    printf("Pushing value: %d\n", node->value->value);
    printf("Pushing value: %d\n", value->value);

    queue->tail->next = node;
    queue->tail = node;
    // queue->head = queue->tail = node;
    queue->len++;
    return queue;
}

int Pop(Queue* queue)
{
    int value = 0;
    Node* to_del = queue->head;
    if (queue->len--) {
        value = queue->head->value->value;
        queue->head = queue->head->next;
        free(to_del);
    }
    return value;
}

void Clear(Queue* queue)
{
    while (queue->head) {
        Pop(queue);
    }

    queue->head = queue->tail = NULL;
}

void Print(const Queue* queue)
{
    const Node* node = queue->head;

    for (; node; node = node->next) {
        printf("%d ", node->value->value);
    }
    printf("\n");
}

int factorial(int n)
{
    if (n == 2) {
        return n;
    }
    return n * factorial(n - 1);
}

int CheckPare(Pare p, Pare* arr, int arr_size)
{
    int i = 0;
    for (i = 0; i < arr_size; i++) {
        if (((arr[i].first.value == p.first.value) && (arr[i].second.value == p.second.value))
            || ((arr[i].first.value == p.second.value) && (arr[i].second.value == p.first.value)))
            return 0;
    }
    return 1;
}

void* ByPassWide(void* args)
{
    Args* params = (Args*)args;
    Queue* q = params->q;
    Graph g = params->g;
    int i = params->i;

    pthread_mutex_lock(&lock);

    Vertex* v = q->head->value;
    //printf("%d\n", v.value);

    if (g.g_elems[i].used == 1)
        cycle = 1;

    if (g.adj_matrix[v->num][i] == 1 && g.g_elems[i].used == 0) {
        q = Push(q, &g.g_elems[i]);
        g.g_elems[i].used = 1;
    }

    v->used = 1;
    Pop(q);

    pthread_mutex_unlock(&lock);

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
    graph.g_elems = (Vertex*)malloc(sizeof(Vertex) * graph.el_num);

    while (i < graph.el_num) {
        printf("Enter %d element:\n", i + 1);
        scanf("%d", &graph.g_elems[i].value);
        graph.g_elems[i].num = i;
        graph.g_elems[i].used = 0;
        //printf("%d\n", graph.g_elems[i].num);
        ++i;
    }

    int max_links = factorial(graph.el_num);
    graph.g_links = (Pare*)malloc(sizeof(Pare) * max_links);

    for (i = 0; i < max_links; i++) {
        graph.g_links[i].first.value = graph.g_links[i].second.value = 0;
    }

    for (i = 0; i < max_links && getchar() != EOF;) {
        printf("Enter next link:\n");
        scanf("%d%d", &pare.first.value, &pare.second.value);
        if (pare.first.value <= graph.el_num && pare.second.value <= graph.el_num && pare.first.value != pare.second.value)
            if (CheckPare(pare, graph.g_links, i + 1) == 1) {
                graph.g_links[i].first.value = pare.first.value;
                graph.g_links[i].second.value = pare.second.value;
                ++i;
            }
    }

    max_links = i;

    graph.adj_matrix = 0;
    graph.adj_matrix = (int**)malloc(sizeof(int*) * graph.el_num);
    printf("%d \n", graph.el_num);
    for (i = 0; i < graph.el_num; ++i) {
        graph.adj_matrix[i] = (int*)malloc(sizeof(int) * graph.el_num);
    }

    int j;
    for (i = 0; i < graph.el_num; i++)
        for (j = 0; j < graph.el_num; j++)
            graph.adj_matrix[i][j] = 0;

    for (i = 0; i < max_links; i++) {
        graph.adj_matrix[graph.g_links[i].first.value - 1][graph.g_links[i].second.value - 1] = 1;
        graph.adj_matrix[graph.g_links[i].second.value - 1][graph.g_links[i].first.value - 1] = 1;
    }

    for (i = 0; i < graph.el_num; i++) {
        for (j = 0; j < graph.el_num; j++)
            printf("%d ", graph.adj_matrix[i][j]);
        putchar('\n');
    }

    pthread_t threads[NUM_OF_THREADS];
    int status = 0;
    int status_addr = 0;

    Queue* queue = Create();

    queue = Push(queue, &graph.g_elems[0]);
    // printf("%d\n", queue->head->value->value);
    graph.g_elems[0].used = 1;

    Args params;
    params.q = queue;
    params.g = graph;

    while (queue->len != 0) {
        for (i = 0; i < graph.el_num; ++i) {
            params.i = i;
            status = pthread_create(&threads[i], NULL, ByPassWide, (void*)&params);

            if (status != 0) {
                printf("pthread_create error\n");
                exit(ERROR_CREATE_THREAD);
            }
        }
    }

    for (i = 0; j < graph.el_num; ++j) {
        status = pthread_join(threads[j], NULL);
        if (status != 0) {
            printf("pthread_join error\n");
            exit(ERROR_JOIN_THREAD);
        }
    }

    if (cycle == 0)
        printf("There are no cycles in that graph\n");

    else
        printf("There is a cycle\n");

    Clear(queue);
    free(queue);

    for (i = 0; i < graph.el_num; i++) {
        free(graph.adj_matrix[i]);
    }

    free(graph.adj_matrix);
    free(graph.g_elems);
    free(graph.g_links);

    pthread_mutex_destroy(&lock);

    return 0;
}