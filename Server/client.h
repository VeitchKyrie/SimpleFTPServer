//
// Created by simon on 21/01/19.
//

#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

    typedef struct
    {

        SOCKET sock;
        char user[1024];

    }Client;

#endif //SERVER_CLIENT_H
