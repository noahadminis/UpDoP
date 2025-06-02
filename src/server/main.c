#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "resources.h"

int main()
{
    char buf[BUFFER_SIZE];

#ifdef DEBUG
    printf("Starting server....\n");
#endif


    int sock_fd_server = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd_server = -1)
    {
        perror("socket():");
        return 1;
    }
    
#ifdef DEBUG
    printf("socket created successfully\n");
#endif

    struct sockaddr_in host_addr;
    int host_addrlen = sizeof(host_addr);

    struct sockaddr_in client_addr;
    int client_addrlen = sizeof(client_addr);

    host_addr.sin_family = AF_INET;
    host_addr.sin_port = htons(PORT);  
    host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sock_fd_server, (struct sockaddr *)&host_addr, host_addrlen) != 0) {
        perror("bind():");
        return 1;
    }

#ifdef DEBUG
    printf("socket successfully bound to address\n");
#endif

    if (listen(sock_fd_server, SOMAXCONN) != 0) {
        perror("listen()");
        return 1;
    }

#ifdef DEBUG
    printf("server listening for connections\n");
#endif

    while(1)
    {
        int sock_fd_client = accept(sock_fd_server, (struct sockaddr *)&client_addr, client_addrlen);
        if (sock_fd_client = -1)
        {
            perror("accept()");
            return 1;
        }
        
#ifdef DEBUG
        printf("accepted connection\n");
#endif

        intptr_t *arg = malloc(sizeof(intptr_t));
        *arg = sock_fd_client;

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)arg);

    }
    return 0;
}