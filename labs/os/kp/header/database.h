#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

template <class T>
class database{
public:
    database();
    ~database();

    void open(char * path);

    pair<bool, size_t> find(const T & value);
    void add(const T & value);
    

private:
    char * path;
};

#endif