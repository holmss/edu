#include "iostream"
#include "fstream"
#include "vector"

inline int ToInt (const char *s) {
    return atoi(s);
}
void GenerateTests(int argc, char *argv[]){
    srand(time(0));
    int n = 1000;
    int counter = 1;

    if (argc > 1) {
        n = ToInt(argv[1]);
    }
    if (argc > 2) {
        counter = ToInt(argv[2]);
    }

    std::ifstream file("inp.txt");

    if (file) {

        std::string inp;
        char tmpChar;
        //file >> tm;
        while (file.get(tmpChar)) {
            //file >> tm;
            if ((tmpChar >= 'a' && tmpChar <= 'z') ||
                (tmpChar >= 'A' && tmpChar <= 'Z') ||
                tmpChar == ' ') {
                inp += tmpChar;
            }
        }
        std::vector <std::string> inpArr;
        std::string tmpString;
        //отделяем слова
        for (char j : inp) {
            if (j == ' ' ||
                j == '\n') {
                inpArr.push_back(tmpString);
                tmpString = "";
            }
                tmpChar = std::tolower(j);
            if (j != ' ' &&
                j != '\n') {
                tmpString += tmpChar;
            }
        }

        for (int testIndex = 0; testIndex < counter; ++testIndex) {
            std::ofstream out("tests/test" + std::to_string(testIndex + 1) + ".t");

            int patternWordCount = rand() % 10;
            int pos = rand() % inpArr.size();

            if (inpArr.size() > 0) {
                //pattern
                for (int j = pos; j < inpArr.size() && j < pos + patternWordCount; ++j) {
                    out << inpArr[j];
                }
                out << std::endl;
                //text
                for (int i = 0; i < n; ++i) {
                    int randIndex = rand() % inpArr.size();
                    for (int j = randIndex;
                         j < inpArr.size() &&
                         j < randIndex + 20; ++j) {
                        out << inpArr[j];
                    }
                }
            }
            out.close();
        }
    }
    file.close();
}
int main (int argc, char *argv[]) {
    GenerateTests(argc,argv);
    return 0;
}
