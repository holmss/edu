#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#include "zmq.h"
#include "chat.c"
#include "message.h"


#define ERROR_CREATE_OR_OPEN_FILE 8

FILE * out;

void *SendRecv(void *arg)
{
    message_t *md = (message_t *) arg;
    zmq_msg_t message;
    zmq_msg_init_size(&message, sizeof(message_t));
    memcpy(zmq_msg_data(&message), md, sizeof(message_t));
    zmq_msg_send(&message, md->requester, 0);
    zmq_msg_close(&message);

    zmq_msg_init(&message);
    zmq_msg_recv(&message, md->requester, 0);
    md = (message_t *) zmq_msg_data(&message);
    printf("%s\n", md->string);
    zmq_msg_close(&message);
    pthread_exit(NULL);
    return 0;
}

void Fout(char * src)
{
    out = fopen(src, "r");
    if(!out)
    {
        perror("can`t open file");
        return;
    }

    char c;
    while((c = fgetc(out)) != EOF)
    {
        printf("%c", c);
    }

    fclose(out);
}

void Chat (void * sendSocket, message_t md)
{
    // char message[MAX_STRING];
    // char c;
    // int i = 0;


    // while(gets(&message) && !(message[0] == '!' && message[1] == 'q'))
    // {
        // printf("(%d)>\t", md.rcv_id);

        // scanf("%s", &message);
        // while(scanf("%s", &message) && i < MAX_STRING)
        // {
        //     // scanf("%s", &message);
        //     // message[i] = c;
        //     ++i;
        // }

        // gets(&message);

        // strcpy(md.string, message);
        long int ttime;
        ttime = time(NULL);
        strcpy(md.date_time, ctime(&ttime));

        pthread_t th;
        md.requester = sendSocket;
        pthread_create(&th, NULL, SendRecv, &md);
        pthread_detach(th);

        fprintf(out, "%d\t%s\t%s\n", md.user_id, md.string, md.date_time);
    // }
    
}

// void Menu ()
// {
//     //printf(":!login : Create new user\n");
//     //printf(":!choose : Choose the chat\n");
//     printf("start : Start new chat\n");
//     // printf(":!exit : Exit\n");
// }

int main(int argc, char **argv)
{
    void *context = zmq_ctx_new();

    int client_ID;
    int action;
    // char action[10];
    
    printf("Enter client's id: ");
    scanf("%d", &client_ID);

    void *sendSocket = zmq_socket(context, ZMQ_REQ);
    zmq_connect(sendSocket, "tcp://localhost:5555");

    do
    {
        // Menu();
        printf("Choose the action: ");
        scanf("%d", &action);
        
        message_t md;
        // strcpy(md.action, action);
        md.user_id = client_ID;
        // strcpy(md.action, "send");

        // if(out)
        //     fclose(out);

        // if(strcmp(action, ":!start"))
        // {
        //     int receiver;
        //     printf("Enter receiver id: ");
        //     scanf("%d", &receiver);
        //     md.rcv_id = receiver;
            
        //     char source[MAX_STRING];
        //     snprintf(source, sizeof(source), "%s%d_%d%s", "messageDB/chat", client_ID, receiver, ".db");

        //     char source_check[MAX_STRING];
        //     snprintf(source, sizeof(source), "%s%d_%d%s", "messageDB/chat", receiver, client_ID, ".db");

        //     out = fopen(source_check, "r");

        //     if(!out)
        //     {
        //         out = fopen(source, "a");
        //         if(!out)
        //         {
        //             printf("can`t open file");
        //             return ERROR_CREATE_OR_OPEN_FILE;
        //         }
        //     }

        //     Chat(sendSocket, md);
        // }

        // if(strcmp(action, "start"))
        // {
            int receiver;
            printf("Enter receiver id: ");
            scanf("%d", &receiver);
            md.rcv_id = receiver;
            
            char source[MAX_STRING];
            snprintf(source, sizeof(source), "%s%d_%d%s", "messageDB/chat", client_ID, receiver, ".db");

            out = fopen(source, "r");
            if(!out)
            {
                char source_check[MAX_STRING];
                snprintf(source_check, sizeof(source_check), "%s%d_%d%s", "messageDB/chat", receiver, client_ID, ".db");

                out = fopen(source_check, "r");

                if(out)
                {
                    Fout(source_check);
                }
                out = fopen(source_check, "a");
                if(!out)
                {
                    printf("can`t open file");
                    return ERROR_CREATE_OR_OPEN_FILE;
                }
            }
            else
            {
                Fout(source );
                out = fopen(source, "a");
                if(!out)
                {
                    printf("can`t open file");
                    return ERROR_CREATE_OR_OPEN_FILE;
                }
            }

            // char message_s[MAX_STRING];

            // do
            // {    
                printf("(%d)>\t", md.rcv_id);

                char msg[MAX_STRING];
                scanf("%s", &msg);
                strcpy(md.string, msg);
                
                Chat(sendSocket, md);

                if(out)
                    fclose(out);
            // } while(message_s[0] != '1' || message_s[1] != 'q');

        // }

        // else if(strcmp(action, ":!exit"))
        // {
        //     break;
        // }

    } while (action != 2);
    
    if(out)
        fclose(out);

    zmq_close(sendSocket);
    zmq_ctx_destroy(context);

    return 0;
}