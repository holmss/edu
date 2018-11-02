#include <cstdlib>
#include <cstdio>

const unsigned int MAX_VALUE = 16;
const unsigned int BYTES_NUMBER = 32;
const unsigned int MAX_STR_LEN = 2048;

struct TItem {
    char md5[BYTES_NUMBER + 1];
    char string[MAX_STR_LEN + 1];
};

int charToDigit(char c) {
    if (c <= 'f' && c >= 'a') {
        return c - 'a' + 10;
    } else {
        return c - '0';
    }
}

void radix_sort(TItem *data, int n, TItem *result) {
    int place[MAX_VALUE];    
    TItem *tmp;
    for (int i = BYTES_NUMBER - 1; i >= 0; --i) {
        int j;
        for (j = 0; j < MAX_VALUE; ++j) {
            place[j] = 0;
        }
        for (j = 0; j < n; ++j) {
            ++place[charToDigit(data[j].md5[i])];
        }
        for (j = 1; j < MAX_VALUE; ++j) {
            place[j] += place[j-1];
        }
        for (j = n - 1; j >= 0; --j) {
            result[--place[charToDigit(data[j].md5[i])]] = data[j];
        }
        tmp = data;
        data = result;
        result = tmp;
    }
}

int main(int argc, char *argv[]) {
    int n = 0, capacity = 32;
    TItem *data = (TItem *)calloc(capacity, sizeof(TItem));
    while (scanf("%s\t%s", data[n].md5, data[n].string) != EOF) {
        ++n;
        if (capacity <= n) {
            capacity *= 2;
            data = (TItem *)realloc(data, capacity * sizeof(TItem));
        }
        getchar();
    }
    TItem *temp_data = (TItem *)calloc(n + 1, sizeof(TItem));
    radix_sort(data, n, temp_data);
    for (int i = 0; i < n; ++i) {
        printf("%s\t%s\n", data[i].md5, data[i].string);
    }
    free(temp_data);
    free(data);
}
