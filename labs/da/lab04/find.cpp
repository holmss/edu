#include "find.h"

namespace NFind {
    std::vector<size_t> ZFunction (const TString& string) {
      size_t n = string.size();
      std::vector<size_t> z(n, 0);
      for(size_t i = 1, l = 0, r = 0; i < n; ++i) {
        if(i <= r) {
          z[i] = std::min(z[i - l], r - i + 1);
        }
        while(i + z[i] < n && string[i + z[i]] == string[z[i]]) {
          ++z[i];
        }
        if(i + z[i] - 1 > r) {
          l = i;
          r = i + z[i] - 1;
        }
      }
      return z;
    }

    std::vector <size_t> Preprocessing (const TString& string) {
        auto z_function = ZFunction(string);
        size_t n = z_function.size();
        std::vector<size_t> strong_sp(n, 0);
        for (size_t iterator_j = n - 1; iterator_j > 0; --iterator_j) {
            size_t iterator_i = iterator_j + z_function[iterator_j] - 1;
            strong_sp[iterator_i] = z_function[iterator_j];
        }
        return strong_sp;
    }

    void Recount (std::pair<size_t, size_t>& curr, char delim) {
        if (delim == ' ') {
            ++(curr.second);
        } else {
            ++(curr.first);
            curr.second = 0;
        }
        return;
    }
    void Recount (std::istream& input_stream, std::pair<size_t, size_t>& curr) {
        char delim;
        while (input_stream.get(delim)) {
            if ((delim >= '0') && (delim <= '9')) {
                input_stream.unget();
                break;
            }
            if (delim == '\n') {
                Recount(curr, delim);
            }
        }
        Recount(curr, ' ');
    }
    std::queue<std::pair<size_t, size_t> > Find (
            const TString& pattern,
            std::istream& input_stream) {
        std::queue<std::pair<size_t, size_t> > answer;
        if (pattern.size() == 0) return answer;
        auto pattern_preprocessing = Preprocessing(pattern);
        std::istream_iterator<TWord> eos;
        size_t p = 0;
        std::pair<size_t, size_t> curr(1, 0);
        Recount(input_stream, curr);
        std::queue<std::pair<size_t, size_t> > entry;
        std::istream_iterator<TWord> input_iterator(input_stream);
        while (input_iterator != eos) {
            while (p < pattern.size() && (pattern[p] == *input_iterator)) {
                ++p;
                entry.push(curr);
                if (entry.size() > pattern.size()) entry.pop();
                Recount(input_stream, curr);
                ++input_iterator;
            }
            if (p == pattern.size()) answer.push(entry.front());
            if (p == 0) {
                entry.push(curr);
                if (entry.size() > pattern.size()) entry.pop();
                Recount(input_stream, curr);
                ++input_iterator;
            }
            p = (p == 0) ? 0 : (pattern_preprocessing[p - 1]);
        }
        return answer;
    }
}
