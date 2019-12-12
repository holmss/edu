#ifndef CLIENT_CONSOLE_H
#define CLIENT_CONSOLE_H 1

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <list>
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/ioctl.h>

#include "connection.h"
#include "person.h"
#include "notify.h"

struct ListenerArgs;
struct ListenerFlags;
struct MessagingListenerArgs;
struct ScreenCheckerArgs;
struct RedrawArgs;

void    ListenerArgsInit(struct ListenerArgs* args, connection *, person*);
void    ListenerFlagsInit(struct ListenerFlags *listenerFlags);
void    RunListener(void* (*listener)(void*), struct ListenerArgs* args);
void*   Listener(void *args);
void*   MessagingListener(void*);
void    StopListener(struct ListenerArgs * args, bool print);
void*   ScreenCheker(void* args);
void    Redraw(person * client, string friend_name);
void    AnswerHelp();

class client_console{
public:
    const size_t count_of_first_messages = 10;

    client_console();
    ~client_console();

    void MainMenu();
    bool OpenMessaging(const string & friend_name);
    static void SendMessage(const string & message);
    static void SendError(const string & error);

private:
    bool FindPerson(const string & s);
    bool ParceMainCommand();
    bool ParceMessagingCommand();
    bool ParceAnswer();

    person p;
    connection connect;
};

#endif