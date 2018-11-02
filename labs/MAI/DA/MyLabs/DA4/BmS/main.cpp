#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <deque>
#include <vector>


typedef struct _Tposition{
    int line;
    int row;
} TPosition;
TPosition nowWord = {1, 1};


void PreBmBc(std::vector<std::pair<std::string, int> > &pattern, std::vector<int>& array) {
    for (int i = 0; i < pattern.size() - 2; ++i) {
        array[pattern[i].second] = pattern.size() - 1 - i;
    }
}


//Длина наибольшего суффикса, который является суффиксом всей строки
void BuildNblock(const std::vector<std::pair<std::string, int > > &pattern, std::vector<int>& N) {
    for (int i  = pattern.size() - 2, l = pattern.size() - 1, r = pattern.size() - 1; i >= 0; --i) {
        if (i >= l) {
            N[i] = std::min((int)(i - l + 1), N[pattern.size() - 1 - r + i]);
        }

        while (i - N[i] >= 0 && pattern[pattern.size() - 1 - N[i]].first == pattern[i - N[i]].first) {
            ++N[i];
        }

        if (i - N[i] + 1 < l) {
            l = i - N[i] + 1;
            r = i;
        }
    }
}

void BuildLblock(std::vector<int>& L, const std::vector<int>& N) {
    for (int j = 0; j < L.size()-1; j++) {
        L[L.size()-N[j]] = j+1;
    }
}
void BuildlBlock(std::vector<int>& l, const std::vector<int>& N) {
    l[N.size()] = 0;
    for(int i = N.size()-1; i >= 0; i--) {
        int  j = N.size() - i;
        if (N[j] == j+1) {
            l[i] = j+1;
        }
        else {
            l[i] = l[i+1];
        }
    }
}

void PatternParsing(std::map<std::string, int> &patternDict,
                    std::vector<std::pair<std::string, int> >& allWordPattern);
bool TextParsing(std::deque<std::pair <std::string, TPosition> >&, const int &);


//=====================================================================================


int main() {
    std::map<std::string, int> patternDict;
    std::vector<std::pair<std::string, int > > pattern;
    PatternParsing(patternDict, pattern);
    int patternSize = pattern.size();
    std::deque<std::pair <std::string, TPosition> > text;
    bool flag = TextParsing(text, patternSize);
    if (patternSize == 1) {
        while(flag) {
            if (pattern[0].first == text[0].first) {
                //text.size = 1 because pattern.size == 1
                printf("%d, %d\n", text[0].second.line, text[0].second.row);
            }
            flag = TextParsing(text, patternSize);
        }
        return 0;
    }
    //pattern size > 1
    std::vector<int> N(patternSize, 0);
    std::vector<int> array(patternDict.size(), patternSize);
    std::vector<int> l(patternSize+1, 0);
    std::vector<int> L(patternSize, 0);
    std::deque<int> M(patternSize, 0);
    /* Preprocessing */
    PreBmBc(pattern, array);
    BuildNblock(pattern, N);
    BuildLblock(L, N);
    BuildlBlock(l, N);
    while(flag) {
        int i;
        int shift;
        for(i = patternSize - 1; i >= 0 && pattern[i].first == text[i].first; --i) {
            if (M[i] < N[i]) {
                i -= M[i];
                continue;
            } else {
                if (N[i] == i) {
                    printf("%d, %d\n", text[0].second.line, text[0].second.row);
                    shift = patternSize - l[1];
                    M[patternSize - 1] = patternSize - 1 - i;
                    goto findPattern;
                }
            }
            if (M[i] > N[i] && N[i] < i) {
                M[patternSize - 1] = patternSize - 1 - i;
                i -= N[i];
                break;
            }
            if (M[i] == N[i] && 0 < N[i] && N[i] < i) {
                i -= M[i];
            }
        }
        if(i == -1) {
            printf("%d, %d\n", text[0].second.line, text[0].second.row);
            shift = patternSize - l[1];
            M[patternSize - 1] = patternSize - 1;
            goto findPattern;
        } else {
            M[patternSize - 1] = patternSize - 1 - i;
            int badCharacter = -1;
            //если в алфавите образца нет такого слова, то сдвигаем на всю длину образца.
            std::map<std::string, int>::iterator it = patternDict.find(text[i].first);
            if (it != patternDict.end()) {
                badCharacter = it->second;
            }
            if( badCharacter  == -1) {
                badCharacter  = patternSize;
                // максимум, поэтому если будет выполняться, то и выбираться тоже
            } else {
                //Правило плохого символа
                badCharacter = i - array[badCharacter];
            }
            int goodSuff;
            if(i == patternSize - 1) {//если конец, то смещение на 1
                goodSuff = 1;
            } else {
                i++;
                if (i < patternSize && L[i] > 0) {
                    goodSuff = patternSize - 1 - L[i];
                } else {
                    goodSuff= patternSize - 1 - l[i];
                }
            }
            shift = std::max(std::max(1, badCharacter), goodSuff);
        }
        findPattern:
        flag = TextParsing(text, shift);
        for (int k = 0; k < shift; k++) {
            M.pop_front();
        }
        M.resize(patternSize);
        for (int i = 0; i < shift; i++) {
            M[patternSize - 1 - i] = 0;
        }
    }
    return 0;


}

bool TextParsing(std::deque<std::pair<std::string, TPosition> >& text, const int & countNext) {
    int sizePattern = countNext;
    if (text.size()) {
        sizePattern = text.size();
        for(int i = countNext; i > 0; --i) { //удаляем первые считанные слова
            // чтобы вставить такое же количество новых
            text.pop_front();
        }
    }
    text.resize(sizePattern);
    char ch;
    int i = sizePattern - countNext;
    while(i < sizePattern) {
        while(!isdigit(ch = getchar())) {
            if(ch == EOF) {
                return false;
            }
            if (ch == '\n') {
                ++nowWord.line;
                nowWord.row = 1;
            }
        }
        text[i].first += tolower(ch);
        while(isdigit(ch = getchar())) {//ввод слова полностью
            text[i].first += tolower(ch);
        }
        text[i].second = nowWord;
        if (ch == ' ') {
            nowWord.row++;
        }
        std::ungetc(ch, stdin);
        ++i;
    }
    return true;

}




void PatternParsing(std::map<std::string, int> &patternDict,
                    std::vector<std::pair<std::string, int> >& allWordPattern) {
    char ch;
    int i = 0;
    std::string tmpStr = "";
    bool  inWord = false;
    while ((ch = getchar()) != '\n') {

        if (ch == EOF) {//никогда не выполняется
            return;
        }

        if (isdigit(ch)) {
            if (!inWord) {
                tmpStr += tolower(ch);
            }
        } else { //Если встретили пробел
            if (tmpStr.size()) {
                if (patternDict.find(tmpStr) == patternDict.end()) {
                    patternDict[tmpStr] = i;
                    i++;
                }
                allWordPattern.push_back(std::pair<std::string, int>
                                                 (tmpStr, patternDict[tmpStr]));
                tmpStr = "";
            }
        }
    }
    if (tmpStr.size()) {
        if (patternDict.find(tmpStr) == patternDict.end()) {
            patternDict[tmpStr] = i;
        }
        allWordPattern.push_back(std::pair<std::string, int>
                                         (tmpStr, patternDict[tmpStr]));
    }
    return;

}
