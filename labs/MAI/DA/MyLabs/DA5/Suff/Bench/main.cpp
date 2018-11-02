#include <iostream>

int main () {
    std::string str;
    std::string str2;
    std::cin >> str >> str2;
    int curPos = 0;
    size_t pos = 0;
    int strSize = str.size();
    while (pos!=-1) {
        pos = str2.find(str, curPos);
        
        curPos += pos;
        if (pos == 0) {
            curPos += strSize;
        }
        /*
         if (pos != std::string::npos)
         std::cout << "Found at pos = " << curPos + 1 << "\n";
         else
         std::cout << "Not found\n";
         */
    }
    return 0;
}
