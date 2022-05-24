#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <dirent.h>
#include <sys/wait.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT 5000
#define SIZE 1024
int sock = -1;
int stdout_fd;

void *reciver(void *args)
{
    char buffer[SIZE];

    int b = 0;
    while (1)
    {
        int b = recv(sock, buffer, SIZE, 0);
        if (b == 0)
        {
            break;
        }
        buffer[b - 1] = '\0';
        printf("%s\n", buffer);
        fflush(stdout);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    stdout_fd = dup(1);

    struct sockaddr_in serverAddress;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, (const char *)SERVER_IP_ADDRESS, &serverAddress.sin_addr);

    if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1)
    {
        sock = -1;
        printf("faield to connect , ip %s port %d\n", SERVER_IP_ADDRESS, SERVER_PORT);
        return 0;
    }


    pthread_t thread_id;
    pthread_create(&thread_id, NULL, reciver, NULL);
    
    char buffer[1024];
    while (strcmp(buffer, "EXIT\n"))
    {
        fgets(buffer, 1024, stdin);
        dup2(sock, 1);
        printf("%s", buffer);
        fflush(stdout);
        dup2(stdout_fd, 1);
    }

    pthread_cancel(thread_id);

    return 0;
}
