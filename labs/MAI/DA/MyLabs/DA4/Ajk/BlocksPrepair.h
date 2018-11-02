#ifndef BLOCKSPREPAIR_H
#define BLOCKSPREPAIR_H

#include <deque>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cstdio>

void BuildNblock (
        const std::vector <std::pair <std::string, int>> &pattern, std::vector <int> &N,
        const int &size);

void BuildStrongeLeftBlock (std::vector <int> &left, const std::vector <int> &N, const int &size);

void BuildLightLeftBlock (std::vector <int> &left, const std::vector <int> &N, const int &size);

#endif //LAB4_BLOCKSPREPAIR_H
