#include <ctime>
#include "Radix.h"
#include <ctime>

void CountingSort (int N, Vector &vector, uint64_t k, int left, int right) {
    int *C = (int *) malloc(sizeof(int) * (k + 1));  // 0..k
    Vector tempVector;
    Create(tempVector, N);     // N+1
    for (int i = 0; i <= k; i++) {  //обнуляем массив из к
        C[i] = 0;
    }
    for (int j = 0; j < N; j++) {//подсчитываем, сколько каких в А из к
        uint64_t index = FindDigit(Load(vector, j), left, right);

        C[index] = C[index] + 1;
    }
    for (int i = 1; i <= k; i++) {  //подсчитываем кол-во элементов, не прев i
        C[i] = C[i] + C[i - 1];
    }
    for (int j = N - 1; j >= 0; j--) {
        uint64_t index = FindDigit(Load(vector, j), left, right);
        Save(tempVector, C[index] - 1, Load(vector, j));
        C[index]--;
        // B[C[A[j]]] = A[j];
        // C[A[j]] = C[A[j]] - 1;
    }

    int vectorSize = Size(tempVector);
    for (int i = 0; i < vectorSize; i++) {
        Save(vector, i, Load(tempVector, i));
    }
    Destroy(tempVector);
    free(C);
}

void RadixSort (Vector &vector, int N) {
    clock_t start = clock();
    /*math counts for radix sort*/
    int b = sizeof(uint64_t) * 8;
    int r = SetLogNum(RoundDown(log2(N)));
    uint64_t k = 1;

    for (int i = 1; i <= r; i++) {
        k *= 2;
    }
    k--;
    int left = b - r;
    int right = b - r;
    int i;
    for (i = r; i <= b; i += r) {
        if (left > b - i) {
            left = 0;
            right += b - i;
        }
        CountingSort(N, vector, k, left, right);
        left -= r;
    }
    clock_t end = clock();
    printf("\nRadix SortTime = %f\n", (double)(end - start)/CLOCKS_PER_SEC);
}

uint64_t FindDigit (Item &item, int left, int right) {
    uint64_t temp = item.key;
    temp <<= left;
    temp >>= right;
    return temp;
}

int RoundDown (double t) {
    int result = 0;
    double val;
    modf(t, &val);
    result = val;
    return result;
}

int SetLogNum (int r) {
    int counter=1;
    while(counter<r){
        counter*=2;
    }
    int prevCounter = counter/2;
    if(counter-r<=r-prevCounter){
        r=counter;
    }else{
        r=prevCounter;
    }
    if(r>64){
        r=64;
    }
    return r;
}
