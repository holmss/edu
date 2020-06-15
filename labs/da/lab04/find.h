#ifndef FIND_H
#define FIND_H

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <queue>
#include <tuple>

namespace NFind {
    using TWord = unsigned int;
    using TString = std::vector<TWord>;

    std::vector<size_t> ZFunction (const TString& string);
    std::vector <size_t> Preprocessing (const TString& string);
    void Recount (std::pair<size_t, size_t>& curr, char delim);
    void Recount (std::istream& input_stream, std::pair<size_t, size_t>& curr);
    std::queue<std::pair<size_t, size_t> > Find (
            const TString& pattern,
            std::istream& input_stream);
}

#endif
