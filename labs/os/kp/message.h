#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
                          
#define MAX_STRING 256    /* максимальная длина строки */

typedef struct            /* структура сообщения */
{
    int user_id;
    int rcv_id;
    char date_time[MAX_STRING];
    char string[MAX_STRING];
    void *requester;
    char action[MAX_STRING];
} message_t;

#endif