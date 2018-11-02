#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include "BlocksPrepair.h"

typedef struct {
    int line;
    int row;
    int skip;
} Pos;
Pos noWord = {1, 1, -1};


void Preprocess (
        std::vector <std::pair <std::string, int>> &pattern,
        std::vector <int> &arr, const int &size) {
    for (int i = 0; i < size - 1; ++i) {
        arr[pattern[i].second] = i;
    }
}

bool TextParse (
        std::deque <std::pair <std::string, Pos>> &txt,
        const int &nextCount) {
    int patternSize = nextCount;
    if (txt.size()) {
        patternSize = txt.size();
        for (int i = nextCount; i > 0; --i) {
            txt.pop_front();
        }
    }
    txt.resize(patternSize);
    char ch;
    int i = patternSize - nextCount;
    bool zeroLead = true;
    while (i < patternSize) {
        while (!isdigit(ch = getchar_unlocked())) {
            if (ch == EOF) {
                return false;
            }
            if (ch == '\n') {
                ++noWord.line;
                noWord.row = 1;
            }
        }
        do {
            if ((ch == '0' && !zeroLead)) {
                txt[i].first += ch;
            }
            if (ch > '0' && ch <= '9') {
                txt[i].first += ch;
                zeroLead = false;
            }
        } while (isdigit(ch = getchar_unlocked()));
        if (txt[i].first.size() == 0) {
            txt[i].first = "0";
        }
        txt[i].second = noWord;
        if (ch == ' ') {
            noWord.row++;
        }
        zeroLead = true;
        std::cin.putback(ch);
        ++i;
    }
    return true;
}

void PatternParsing (
        std::unordered_map <std::string, int> &dictPatt,
        std::vector <std::pair <std::string, int>> &arAll) {
    char ch;
    int i = 0;
    bool zero = true;
    bool word = false;
    std::string tmpStr = "";
    while ((ch = getchar_unlocked()) != '\n') {

        if (ch == EOF) {//никогда не выполняется
            return;
        }

        if (isdigit(ch)) {
            if (ch == '0' && !zero) {
                tmpStr += ch;
            }
            if (ch > '0' && ch <= '9') {
                zero = false;
                tmpStr += ch;
            }
            word = true;
        } else {
            if (word) {
                if (tmpStr.size() == 0) {
                    tmpStr = "0";
                }
                if (dictPatt.find(tmpStr) == dictPatt.end()) {
                    dictPatt[tmpStr] = i;
                    i++;
                }
                arAll.push_back(std::pair <std::string, int>
                                            (tmpStr, dictPatt[tmpStr]));
                tmpStr = "";
                zero = true;
                word = false;
            }
        }
    }
    if (tmpStr.size() == 0 && word) {
        tmpStr = "0";
    }
    if (tmpStr.size()) {
        if (dictPatt.find(tmpStr) == dictPatt.end()) {
            dictPatt[tmpStr] = i;
        }
        arAll.push_back(std::pair <std::string, int>
                                    (tmpStr, dictPatt[tmpStr]));
    }
}

int main () {
    std::unordered_map <std::string, int> dct;
    std::vector <std::pair <std::string, int>> patt;
    std::deque <std::pair <std::string, Pos>> txt;

    PatternParsing(dct, patt);
    int pattSize = patt.size();

    bool flag = TextParse(txt, pattSize);
    if (pattSize == 1) {
        while (flag) {
            if (patt[0].first == txt[0].first) {
                printf("%d, %d\n", txt[0].second.line, txt[0].second.row);
            }
            flag = TextParse(txt, pattSize);
        }
        return 0;
    }

    std::vector <int> nBlock(pattSize, 0);
    std::vector <int> arr(dct.size(), pattSize);
    std::vector <int> lightLeftBlock(pattSize + 1, 0);
    std::vector <int> strongeLeftBlock(pattSize, 0);

    Preprocess(patt, arr, pattSize);
    BuildNblock(patt, nBlock, pattSize);
    BuildStrongeLeftBlock(strongeLeftBlock, nBlock, pattSize);
    BuildLightLeftBlock(lightLeftBlock, nBlock, pattSize);

    while (flag) {
        int i;
        int shift;
        for (i = pattSize - 1; i >= 0; --i) {
            if (txt[i].second.skip == -1 || (txt[i].second.skip == 0 && nBlock[i] == 0)) {
                if (txt[i].first == patt[i].first) {
                    if (i == 0) {
                        printf("%d, %d\n", txt[0].second.line, txt[0].second.row);
                        txt[pattSize - 1].second.skip = pattSize;
                        shift = pattSize - lightLeftBlock[1];
                        break;
                    }
                    continue;
                } else {
                    txt[pattSize - 1].second.skip = pattSize - 1 - i;
                    break;
                }
            }
            if (txt[i].second.skip < nBlock[i]) {
                i -= txt[i].second.skip;
                continue;

            } else if (txt[i].second.skip >= nBlock[i] && nBlock[i] == i) {
                printf("%d, %d\n", txt[0].second.line, txt[0].second.row);
                shift = pattSize - lightLeftBlock[1];
                txt[pattSize - 1].second.skip = pattSize - 1 - i;
                break;
            }
            if (txt[i].second.skip > nBlock[i] && nBlock[i] < i) {
                txt[pattSize - 1].second.skip = pattSize - 1 - i;
                i -= nBlock[i];
                break;
            }
            if (txt[i].second.skip == nBlock[i] && 0 < nBlock[i] && nBlock[i] < i) {
                i -= txt[i].second.skip;
            }
        }
        if (i == -1) {
            printf("%d, %d\n", txt[0].second.line, txt[0].second.row);
            shift = pattSize - lightLeftBlock[1];
            txt[pattSize - 1].second.skip = pattSize - 1;
            flag = TextParse(txt, shift);
            continue;
        } else {
            txt[pattSize - 1].second.skip = pattSize - 1 - i;
            int badCh = -1;
            std::unordered_map <std::string, int>::iterator it = dct.find(txt[i].first);
            if (it != dct.end()) {
                badCh = it->second;
            }
            if (badCh == -1) {
                badCh = pattSize;
            } else {
                badCh = std::max(1, i - arr[badCh]);
            }
            int goodSuf;
            if (i == pattSize - 1) {
                goodSuf = 1;
            } else {

                if (i < pattSize && strongeLeftBlock[i + 1] > 0) {
                    goodSuf = pattSize - 1 - strongeLeftBlock[i + 1];
                } else {
                    goodSuf = pattSize - lightLeftBlock[i + 1];
                }
            }
            shift = std::max(badCh, goodSuf);
        }
        flag = TextParse(txt, shift);
    }
    return 0;
}