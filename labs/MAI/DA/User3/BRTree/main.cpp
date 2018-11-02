#include <string.h>
#include "BRTree.h"
#include <iostream>
#include <ctime>

void Parse(char& choice,char* temp,uint64_t& data);
int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);
    
    char choice;
    if (!std::cin.get(choice)) {
        return 0;
    }
    clock_t start = clock();
    TRBTree *tree = new TRBTree();
    const int size = 257;
    char *temp = new char[size];
    uint64_t data = 0;


    std::cin.putback(choice);


    while (true) {
        Parse(choice,temp,data);
        if(choice=='E'){
            break;
        }
        switch (choice) {
            case '+': {

                if (tree->RBInsert(temp, data)) {
                    std::cout << "OK\n";
                } else {
                    std::cout << "Exist\n";
                }
                //delete newNode;
            }
                break;
            case '-': {
                TRBNode *tempNode = tree->Search(temp);
                if (tempNode != (tree->nil)) {
                    tree->RBDelete(tempNode);
                    std::cout << "OK" << '\n';;
                } else {
                    std::cout << "NoSuchWord\n";
                }
                //tempNode= nullptr;
            }
                break;
            case 'S': {

                    std::ofstream file(temp);

                    if (!file) {
                        std::cout << "ERROR: Couldn't create file\n";
                    } else {
                        tree->Serialize(tree->root, file);
                        std::cout << "OK\n";
                    }
                    file.close();
                }
            break;
            case 'L':{
                    std::ifstream file(temp, std::ifstream::binary);
                    if (!file) {
                        std::cout << "ERROR: Couldn't open file!\n";
                    } else {
                        delete tree;
                        tree = new TRBTree();
                        char *tmp = new char[257];
                        tree->DeSerialize(tree->nil, tree->root, file, tmp);
                        std::cout << "OK\n";
                        delete[] tmp;
                        file.close();
                    }
                }
                break;

            default: {

                TRBNode *answer = tree->Search(temp);

                if (answer == (tree->nil) || answer == nullptr) {
                    std::cout << "NoSuchWord\n";
                } else {
                    std::cout << "OK: " << answer->value << '\n';
                }
                //answer = nullptr;
                //delete answer;
            }
        }
    }
   // std::cout << sizeof(tree)<< std::endl;

    delete tree;
    delete[] temp;

    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;

    std::ofstream file("time4", std::ios::app);
    file << "Time : " << time << '\n';
    file.close();

    return 0;
}

void Parse(char &choice,char* temp,uint64_t& data){
    char c;
    int i=0;
    data =0;
    c=getchar_unlocked();
    //
    // if ((c=getchar_unlocked())==EOF){
    if(c==EOF|| c==' '){
        choice='E';
        return;
    }
    switch (c){
        case '+': {
            i=0;
            choice = c;
            getchar_unlocked();
            while ((c = tolower(getchar_unlocked())) != ' ') {
               // std::cout<<c<<std::endl;
                temp[i++] = c;
            }
            temp[i] = '\0';
            while ((c = getchar_unlocked()) != '\n') {
                data = data * 10 + c - '0';
            }
            break;
        }
        case '-':{
            i=0;
            choice = c;
            getchar_unlocked();
            while ((c = tolower(getchar_unlocked())) != '\n') {
                temp[i++] = c;
            }
            temp[i] = '\0';

            break;
        }
        case '!':{
            getchar_unlocked();
            choice =getchar_unlocked();
//            for (int i=0;i++;i<4){
//                getchar_unlocked();
//            }
            getchar_unlocked();
            getchar_unlocked();
            getchar_unlocked();
            getchar_unlocked();
            i = 0;
            while((c = getchar_unlocked()) != '\n') {
                temp[i++] = c;
            }
            temp[i] = '\0';
            break;
        }
//        case EOF:{
//            choice='E';
//            break;
//
//        }
        default:{
            choice='?';
            i = 1;
            temp[0]=tolower(c);
            while((c = tolower(getchar_unlocked())) != '\n') {
                temp[i++] = c;
            }
            temp[i]='\0';

        }
    }

}