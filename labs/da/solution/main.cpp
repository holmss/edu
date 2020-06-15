#include <map>
#include <string>
#include <iostream>
#include <algorithm>

#include "TSuffixTree.h"

#include <memory>
int main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    std::string text;
    std::cin >> text;
    NTree::TSuffixTree tree(text);
    std::string pattern;
    size_t pattern_count = 0;
    while(std::cin >> pattern) {
        ++pattern_count;
        auto vec = tree.Find(pattern);
        std::sort(vec.begin(), vec.end());
        if (vec.size()) {
            std::cout << pattern_count << ": ";
            for (size_t it = 0; it < vec.size(); ++it) {
                if (it == vec.size() - 1) {
                    std::cout << vec[it];
                } else {
                    std::cout << vec[it] << ", ";
                }
            }
            std::cout << '\n';
        }
    }
    return 0;
}
