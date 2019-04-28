#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int32_t ID;

typedef struct _client
{
    ID client;
    int sum;
} Client;

typedef struct ClientDB
{
    Client cl;
    ClientDB left;
    CLientDB right;
} ClientDB;

ClientDB *ClientDBCreate()
{
    ClientDB *newDB = (ClientDB *)malloc(sizeof(ClientDB));
    newDB->cl = (Client *)malloc(sizeof(Client));
    newDB->left = NULL;
    newDB->right = NULL;

    return newDB;
}

ClientDB *ClientAdd(ClientDB *cDB, ID client)
{
    if (cDB->cl.client == client)
    {
        return cDB;
    }
    if (client < cDB->cl.client)
    {
        cDB->left = ClientAdd(cDB->left, client);
    }
    else
    {
        cDB->right = ClientAdd(cDB->right, client);
    }

    return tree;
}

void ClientDBPrint(ClientDB *cDB, int tab)
{
    if (cDB == NULL)
    {
        return;
    }
    printInorder(cDB->left, tab + 2);
    for (int i = 0; i < tab; ++i)
    {
        putchar(' ');
    }
    printf("%d\n", cDB->cl.client);
    printInorder(cDB->right, tab + 2);
}

Client *ClientFind(ClientDB *cDB, int clientint)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (cDB->cl.client == clientint)
    {
        return (cDB->cl);
    }
    if (clientint < cDB->cl.client)
    {
        return ClientFind(cDB->left, clientint);
    }
    return ClientFind(->right, value);
}