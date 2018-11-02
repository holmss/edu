#include <algorithm>
#include <cassert>
#include <ctime>
#include <iostream>
#include <vector>

bool CheckOrder (const std::vector <std::pair <int, std::string> > &data) {
    for (size_t idx = 1; idx < data.size(); ++idx) {
        if (data[idx - 1].first > data[idx].first) {
            return false;
        }
    }
    return true;
}

bool PairComparer (const std::pair <int, std::string> &a, std::pair <int, std::string> &b) {
    return a.first < b.first;
}
void CountingSort (std::vector <std::pair <int, std::string> >&inp) {
    int size = inp.capacity();
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (inp[i].first > max) {
            max = inp[i].first;
        }
    }
    std::vector <std::pair <int, std::string> >res(size);
    int *countMass = new int[max + 1];
    for (int i = 0; i < max + 1; ++i) {
        countMass[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        countMass[inp[i].first]++;
    }

    for (int i = 1; i <= max; ++i) {
        countMass[i] = countMass[i] + countMass[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        int tmp = countMass[(inp)[i].first] - 1;
        res[tmp] = inp[i];
        countMass[inp[i].first] = countMass[inp[i].first] - 1;
    }
    for (int i = 0; i < size; ++i) {
        inp[i] = res[i];
    }
    delete[] countMass;
}
void StdSort (std::vector <std::pair <int, std::string> > &data) {
    std::sort(data.begin(), data.end(), PairComparer);
}

void RunStdSort (std::vector <std::pair <int, std::string> > &data) {
    clock_t start = clock();
    StdSort(data);
    clock_t end = clock();
    assert(CheckOrder(data) == true);
    double time = (double)(end - start);
    printf("\nStd SortTime = %lf\n",time/CLOCKS_PER_SEC);
}
void RunCountingSort (std::vector <std::pair <int, std::string> > &data) {
    clock_t start = clock();
    CountingSort(data);
    clock_t end = clock();
    assert(CheckOrder(data) == true);
    double time = (double)(end - start);
    printf("\nCounting SortTime = %lf\n",time/CLOCKS_PER_SEC);
}

int main (int argc, const char *argv[]) {
    std::vector <std::pair <int, std::string> > data;
    int tempInt = 0;
    char *bufStr = new char[2048];
    std::pair <int, std::string> pair;
    while (scanf("%d", &tempInt) != EOF) {
        scanf("%s", bufStr);
        pair.first = tempInt;
        pair.second = bufStr;

        data.push_back(pair);
    }
    delete[] bufStr;
    std::vector <std::pair <int, std::string> > dataCopy(data);
    RunStdSort(data);
    RunCountingSort(data);
    return 0;
}
