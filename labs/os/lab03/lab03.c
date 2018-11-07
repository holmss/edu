#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>

//6 вариант
/* Провести распараллеленый поиск по ненаправленному графу в ширину.
Граф задается набором значений, что хранятся в вершинах, и набором пар связей.
Информация по графу хранится в отдельнм файле. 
Необходимо определить, есть ли в графе циклы */

typedef struct TPare 
{
    int first, second;
}Pare;

typedef struct TGraph 
{
    int el_num;
    char *g_elems;
    Pare pare;
    Pare *g_links;
}Graph;

int main() 
{    
    pid_t p;
    int fd[2];
    int pe = pipe(fd);

     if (pe)
        perror("pipe");

    int i = 0;

    Graph graph;
    printf("Enter the number of elements of graph:\n");
    scanf("%d", &graph.el_num);

    while (i < graph.el_num)
    {
        scanf("%c", &graph.g_elems[i]);
        ++i;
    }
    
    while ( )

    return 0;
}