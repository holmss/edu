#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <signal.h>
#include <assert.h>

#include "zmq.h"
#include "chat.c"
#include "message.h"

#define IS_ALREADY_CLIENT 19

volatile sig_atomic_t flag = 0;

void block_func(int sig)
{
    if (!flag) {
        flag = 1;
    } else {
        exit(0);
    }
}

void unblock_func(int sig)
{
    flag = 0;
}

int main(void)
{
    int code;
    userDB userBase = userDBCreate();

    void *context = zmq_ctx_new();
    void *responsSocket = zmq_socket(context, ZMQ_REP);

    zmq_bind (responsSocket, "tcp://*:5555");
    // assert (rc == 0);

    while (1) {
        signal(SIGINT, block_func);
        signal(SIGTSTP, unblock_func);
        if (!flag) {

            zmq_msg_t message;

            zmq_msg_init(&message);
            zmq_msg_recv(&message, responsSocket, 0);
            message_t *md = (message_t *) zmq_msg_data(&message);
            zmq_msg_close(&message);

            char info[MAX_STRING];

            // if(strcmp(md->action, "send"))
            // {
                printf("Send message from account id: %d to account id: %d\n", md->user_id, md->rcv_id);
                code = MessageSend(md->user_id, md->rcv_id, userBase);
                if(code != 0)
                {
                    printf("Not authorized user\n");
                    strcpy(info, "You aren't an authorized user or receiver is not\0");
                }
                else
                {
                    strcpy(info, md->string);
                    // memcpy(md->string, info, strlen(info) + 1);
                    zmq_msg_init_size(&message, sizeof(message_t));
                    memcpy(zmq_msg_data(&message), md, sizeof(message_t));
                    zmq_msg_send(&message, responsSocket, 0);
                    zmq_msg_close(&message);
                }
                // userDBPrint(userBase);/////////DEBUUUUUUUG
                // }

            // else if(strcmp(md->action, ":!choose"))
            // {
            //     printf("Send message from account id: %d to account id: %d\n", md->user_id, md->rcv_id);
            //     code = MessageSend(md->user_id, md->rcv_id, md->string, userBase);
            //     if(code != SUCCESS)
            //     {
            //         printf("Not authorized user\n");
            //         strcpy(info, "You aren't an authorized user or receiver is not\0");
            //     }

            //     memcpy(md->string, info, strlen(info) + 1);
            //     zmq_msg_init_size(&message, sizeof(message_t));
            //     memcpy(zmq_msg_data(&message), md, sizeof(message_t));
            //     zmq_msg_send(&message, responsSocket, 0);
            //     zmq_msg_close(&message);
            // }
            
            zmq_msg_close(&message);
        }
    }

    zmq_close(responsSocket);
    zmq_ctx_destroy(context);

    userDBDestroy(&userBase);

    return 0;
}