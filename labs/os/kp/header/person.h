#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

#include <dirent.h>

#include "connection.h"
#include "constants.h"

using namespace std;

class person{
public:
    person();
    person(connection & connect);
    ~person();

    bool enter(connection & connect);
    void logout(connection & connect);

    string& get_name();
    string& get_passwd();
//    fstream* get_friend(const string & name);
    void list_friends();

    void read_friends();
    void get_ask(const string & name);
    void add_ask(const string & name);
    void show_last_messages(const string & friend_name, size_t count);
    void add_message(const string& fr, const string & sender, const string & message);
    void set_name(const string & new_name);
    void set_passwd(const string & new_passwd);
    void add_friend(const string & friend_name);
    bool is_friend(const string & friend_name);
    bool is_logged();
    vector<string>* get_messages(const string & name);

private:
    void read_messages(const string & friend_name);
    bool login(string & name, string & password, connection & connect);
    bool registrate(const string & name, const string & password, connection & connect);
    bool registrate(connection & connect);

    unordered_map<string, vector<string>> friends;
    set<string> ask_friends;
    string name;
    string passwd;
    bool is_logged_in;
};

#endif