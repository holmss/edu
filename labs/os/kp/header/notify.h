#ifndef NOTIFY_H
#define NOTIFY_H

#include <iostream>
#include <map>
#include <set>
#include <fstream>

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

class notify{
public:
    notify();
    ~notify();

    void show();
    void add_message(const string & name);
    void add_friend_answer(const string & ans);
    void add_friend_ask(const string & ask);
    size_t asks();
    void print_asks();
    bool any_news();

    void save_notifies(const string & directory_path);
    bool read_notifies(const string & directory_path);
    size_t messages_count(const string& name);

    void message_seen(const string & name);
    bool asked(const string & name);

private:
    map<string, size_t> messages;   // name - count of received messages
    set<string> friend_answers;     // people, who answered to friend ask
    set<string> friend_ask;         // people, who asked to be friend;
};

#endif