#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "message.h"

#define NOT_MEMORY -3
#define NOT_CLIENT -2
#define RECEIVER_NOT_CLIENT -1
#define SUCCESS 0

typedef struct /*структура пользователя*/
{
    int id;
    char * tmp_msg[MAX_STRING];
    char passwd[MAX_STRING];
    char username[MAX_STRING];
} *user_t;

typedef struct /*база данных пользователей*/
{
    user_t clients;
    uint32_t size;
    uint32_t freespace;
} *userDB;

userDB userDBCreate(void) //создание базы данных
{
    userDB uDB = (userDB) malloc(sizeof(*uDB));
    if (!uDB) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(NOT_MEMORY);
    }
    uDB->clients = (user_t) malloc(sizeof(*(uDB->clients)));
    uDB->size = 0;
    uDB->freespace = 1;
    return uDB;
}

void DBResize(userDB uDB) //изменение размера бд
{
    uDB->clients = realloc(uDB->clients, 2 * uDB->size * sizeof(*(uDB->clients)));
    if (!uDB->clients) {
        fprintf(stderr, "ERROR: no memory\n");
        exit(NOT_MEMORY);
    }
    uDB->freespace = uDB->size;
}

void userAdd(userDB uDB, int id) //добавление пользователя
{
    if (!uDB->freespace) {
        DBResize(uDB);
    }

    uDB->clients[uDB->size].id = id;
    // strcpy(uDB->clients[uDB->size].passwd, passwd);
    // strcpy(uDB->clients[uDB->size].username, username);
    uDB->size++;
    uDB->freespace--;
}

void userDBPrint(userDB uDB) //вывод базы данных
{
    if (uDB) {
        for (uint32_t i = 0; i < uDB->size; ++i) {
            printf("ID: %d\t", uDB->clients[i].id);
            // printf("NAME: %s\t", uDB->clients[i].username);
            // printf("PASSWORD: %s\n", uDB->clients[i].passwd);
        }
    }
}

user_t userFind(userDB uDB, int clientint) //поиск пользователя
{
    if (uDB) {
        for (uint32_t i = 0; i < uDB->size; ++i) {
            if (uDB->clients[i].id == clientint) {
                return &(uDB->clients[i]);
            }
        }
    }
    return NULL;
}

void userDBDestroy(userDB *uDB) //удаление бд
{
    free((*uDB)->clients);
    (*uDB)->clients = NULL;
    free(*uDB);
    *uDB = NULL;
}

int MessageSend(int Sender, int Receiver, userDB uDB) //проверка наличия юзеров
{
    user_t uSender = userFind(uDB, Sender);
    if (!uSender) {
        userAdd(uDB, Sender);
    }
    user_t uReceiver = userFind(uDB, Receiver);
    if (!uReceiver) {
        return RECEIVER_NOT_CLIENT;
    }
    // strcpy(uReceiver->tmp_msg, md.string);
    return 0;
}

