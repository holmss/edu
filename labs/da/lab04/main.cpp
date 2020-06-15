#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <queue>
#include <tuple>

#include "find.h"

int main() {
    std::string pattern_string;
    std::getline(std::cin, pattern_string);
    std::stringstream stream(pattern_string);
    NFind::TString pattern;
    NFind::TWord word;
    while (stream >> word) {
        pattern.push_back(word);
    }
    std::queue<std::pair<size_t, size_t> > answer = NFind::Find(pattern, std::cin);
    while (!answer.empty()) {
        auto pair = answer.front();
        answer.pop();
        std::cout << pair.first << ", " << pair.second << '\n';
    }
}
