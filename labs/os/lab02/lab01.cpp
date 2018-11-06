#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>

//13 вариант 

//родительский процесс считывает матрицы из стандартного ввода
//дочерний процесс вычисляет среднеарифметическое этих матриц
//родительский процесс печатает результат

void child(int fd_wrt, int *matrix, int n, int m) {
	int    sum = 0, i;
	double res;

	for (i = 0; i < n*m; i++)
		sum += matrix[i];
	
	res = (double)sum/(n*m);
	write(fd_wrt, &res, sizeof(res));
}

void parent(int fd_read) {
	double res;

	read(fd_read, &res, sizeof(res));
	printf("The middle value is: %g\n", res);
}

int main ()
{
    pid_t p;
    int fd[2];
    int pe = pipe(fd);

    if (pe)
        perror("pipe");

    int i = 0;
    int *matrix;
    int n, m;

    printf("Enter the number of matrix elements in format \nlines: \tcolumns:\n");
    scanf("%d%d", &n, &m);
    matrix = (int*)malloc(n*m*sizeof(int));


    for (i = 0; i < m*n; i++)
        scanf("%d", &matrix[i]);//проверка не 0
    
    switch (p = fork())
    {
        case -1: 
            perror ("fork");
            break;
        case 0:
            close(fd[0]);
			child(fd[1], matrix, n, m);
            break;

        default:
            close(fd[1]);
			parent(fd[0]);
    }

    free(matrix);
    return 0;
}