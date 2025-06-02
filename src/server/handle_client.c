#include <sys/socket.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "resources.h"


void *handle_client(void * arg){
    int fd = *(intptr_t *)arg;
    free(arg);

    int opened_file_fd;
    char resp_buffer[BUFFER_SIZE];

    char * buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
    char * read_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));



   ssize_t bytes_received; 

    while ((bytes_received = recv(fd, buffer, BUFFER_SIZE, 0)) > 0)
    {
        
    }
    

    if (bytes_received < 0) {
        perror("webserver (recv)");
        close(fd);
        free(buffer);
        free(read_buffer);
        return 0;
    } else if (bytes_received == 0) {
        // Verbindung wurde vom Client geschlossen
        close(fd);
        free(buffer);
        free(read_buffer);
        return 0;
    }
    
    // Extracting the file name from the HTTP-Request
    char * f = buffer + 5;
    *strchr(f, path_file_end)= 0;
    
    char * path_buf = (char *) malloc(50 * sizeof(char));
    // Kopiert path in path_buf
    strcpy(path_buf, path);
    //fügt zu path_buf f hinzu
    strcat(path_buf, f);
    printf("%s\n", path_buf);

    // Open the requested file
    if ((opened_file_fd = open(path_buf, O_RDONLY)) < 0)
    {
        perror("Failed to open file!");
        send(fd, http_response_not_found, strlen(http_response_not_found), 0);
        close(fd);
        free(buffer);
        free(read_buffer);
        return 0;
    }
    else
    {
        if (read(opened_file_fd, read_buffer, BUFFER_SIZE) < 0)
        {
        perror("Failed reading the file!");
        }
    
        free(path_buf);

        strcpy(resp_buffer, http_response_ok);
        strcat(resp_buffer, read_buffer);

        // Send the content of the file
        if (send(fd, resp_buffer, strlen(resp_buffer), 0) < 0)
        {
            perror("Failed sending data!");
        }
        
        close(fd);
        free(buffer);
        free(read_buffer);
        return EXIT_SUCCESS;
    }

    
}

