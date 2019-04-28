#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

//13 вариант

//родительский процесс считывает матрицы из стандартного ввода
//дочерний процесс вычисляет среднеарифметическое этих матриц
//родительский процесс печатает результат

void child(int fd_wrt, int *matrix, int n, int m)
{
    int sum = 0, i;
    double res;

    for (i = 0; i < n * m; i++)
        sum += matrix[i];

    res = (double)sum / (n * m);
    write(fd_wrt, &res, sizeof(res));
}

void parent(int fd_read)
{
    double res;

    read(fd_read, &res, sizeof(res));
    printf("The middle value is: %g\n", res);
}

int main()
{
    pid_t p;
    int fd[2];
    int pe = pipe(fd);

    if (pe)
        perror("pipe");

    int i = 0;
    int *matrix;
    int n, m;

    // int fd_in;
    // void *src;
    // struct stat statbuf;

    printf("Enter the number of matrix elements in format \nlines: \tcolumns:\n");
    scanf("%d%d", &n, &m);
    matrix = (int *)malloc(n * m * sizeof(int));

    // for (i = 0; i < m*n; i++)
    //     scanf("%d", &matrix[i]);

    int tmp = open("temp_file", O_RDWR | O_CREAT | O_TRUNC);
    if (lseek(tmp, sizeof(int) * n * m, SEEK_SET) == -1)
        perror("memory");
    if (write(tmp, "", 1) != 1)
        perror("temp file write");

    int *src = (int *)mmap(0, sizeof(int) * (m * n + 2), PROT_READ | PROT_WRITE, MAP_SHARED, tmp, 0);

    if (src == (int *)-1)
        perror("source file");

    src[0] = m;
    src[1] = n;

    for (i = 0; i < m * n; i++)
        scanf("%d", &src[i + 2]);

    switch (p = fork())
    {
    case -1:
        perror("fork");
        break;
    case 0:
        close(fd[0]);
        int M, N;
        M = src[0];
        N = src[1];
        int *Matrix;
        Matrix = (int *)malloc(M * N * sizeof(int));
        for (i = 0; i < M * N; i++)
        {
            Matrix[i] = src[i + 2];
        }
        child(fd[1], Matrix, N, M);
        break;

    default:
        close(fd[1]);
        parent(fd[0]);
    }

    munmap((void*)src, sizeof(int) * (m * n + 2));
    close(tmp);
    remove("temp_file");

    free(matrix);
    return 0;
}