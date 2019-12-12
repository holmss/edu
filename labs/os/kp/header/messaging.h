#ifndef MESSAGING_H
#define MESSAGING_H

#include <iostream>
#include <string>

#include "connection.h"
#include "person.h"

class messaging{
public:
    messaging(connection & connect, person & pers, const string & friend_name);
    ~messaging();

    void help();
private:

};

#endif