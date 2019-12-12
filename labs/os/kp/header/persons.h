#ifndef PERSONS_H
#define PERSONS_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <list>
#include <dirent.h>
#include <sys/stat.h>

#include "constants.h"

using namespace std;

typedef struct person{
    string password;
    list<string> notifies;
    bool logged_in;
}person;

class persons{
public:
    const char* path = "persons/";
    
    persons();
    ~persons();

    string check(const string & name);
    int login(const string & person, const string & password);
    void logout(const string & person);
    int registrate(const string & name, const string & password);
    void add_ask(const string & from, const string & to);
    void add_answer(const string & from, const string & to);
    void add_message(const string & from, const string & to, const string & message);
    bool find_person(const string & name);
    unordered_map<string, person>::iterator find(const string & person);

private:
    unordered_map<string, person> data;
    ofstream password_db;
};

#endif