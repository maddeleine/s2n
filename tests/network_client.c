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
    /* We are going to be talking in port 8888 */
    serv_addr.sin_port = htons(8888);

    int connect_result = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (connect_result < 0) {
        printf("Error: connect error\n");
        exit(1);
    }

    char buffer[] =  "Hey there I'm the client";
    int write_result = write(socket_fd, buffer, strlen(buffer));
    if (write_result < 0) {
        printf("Error: write error\n");
        exit(1);
    }

    return 0;
}
