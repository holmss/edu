#include "BlocksPrepair.h"

void BuildNblock (
        const std::vector <std::pair <std::string, int>> &pattern,
        std::vector <int> &N, const int &size) {
    for (int i = size - 1, l = size - 1,
                 r = size - 1; i >= 0; --i) {
        if (i >= l) {
            N[i] = std::min((i - l + 1), N[size - 1 - r + i]);
        }

        while (i - N[i] >= 0 && pattern[size - 1 - N[i]].first == pattern[i - N[i]].first) {
            ++N[i];
        }

        if (i - N[i] + 1 < l) {
            l = i - N[i] + 1;
            r = i;
        }
    }
}

void BuildStrongeLeftBlock (
        std::vector <int> &left,
        const std::vector <int> &N, const int &size) {
    for (int j = 0; j < size; j++) {
        int k = size - N[j];
        left[k] = j;
    }
}

void BuildLightLeftBlock (
        std::vector <int> &left,
        const std::vector <int> &N, const int &size) {
    left[left.size() - 1] = 0;
    int j = 0;
    for (int i = 1; i < size; i++) {
        if (N[i] == i + 1) {
            j = i + 1;
        }
        left[N.size() - 1 - i] = j;
    }
}