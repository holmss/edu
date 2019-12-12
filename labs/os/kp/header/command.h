#ifndef COMAND_H
#define COMAND_H

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class command{
public:
    command();
    ~command();

    void parce_string(const string & s);

    string& get_action();
    string get_next_arg();
    string get_all();

private:
    string action;
    stringstream ss;
};

#endif