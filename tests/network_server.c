#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    /* Creates the socket */
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        printf("Error: socket error\n");
        exit(1);
    }

    struct sockaddr_in serv_addr = { 0 };
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    /* We are going to be listening on port 8888 */
    serv_addr.sin_port = htons(8888);

    /* Tells the socket what address to listen for incoming connections */
    int bind_result = bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    if (bind_result < 0) {
        printf("Error: binding error %s\n", strerror(errno));
        exit(1);
    }

    /* Marks the socket as one that will be used to accept
     * incoming connections. The argument 5 means that this socket
     * can have 5 connections pending on the queue at a time. */
    int listen_result = listen(socket_fd, 5);
    if (listen_result < 0) {
        printf("Error: listen error\n");
        exit(1);
    }

    /* Pulls the first incoming connection off the queue and
     * instantiates a new socket for this connection. */
    int new_socket_fd = accept(socket_fd, NULL, 0);
    if (new_socket_fd < 0) {
        printf("Error: accept error\n");
        exit(1);
    }

    char buffer[256] = { 0 };
    ssize_t read_size = read(new_socket_fd, buffer, 255);
    if (read_size < 0) {
        printf("Error: read error\n");
        exit(1);
    }

    printf("Received message from client: %s\n", buffer);

    return 0;
}
