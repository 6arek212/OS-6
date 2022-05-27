#include "reactor.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

// Get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void accept1(int fd, Reactor *rec, int index)
{
    char buf[256];                      // Buffer for client data
    struct sockaddr_storage remoteaddr; // Client address
    socklen_t addrlen;

    char remoteIP[INET6_ADDRSTRLEN];

    // If listener is ready to read, handle new connection
    addrlen = sizeof remoteaddr;
    int newfd = accept(rec->listener,
                       (struct sockaddr *)&remoteaddr,
                       &addrlen);

    if (newfd == -1)
    {
        perror("accept");
    }
    else
    {
        installHandller(rec, newfd, recv1);

        printf("pollserver: new connection from %s on "
               "socket %d\n",
               inet_ntop(remoteaddr.ss_family,
                         get_in_addr((struct sockaddr *)&remoteaddr),
                         remoteIP, INET6_ADDRSTRLEN),
               newfd);
    }
}

void recv1(int fd, Reactor *rec, int index)
{
    char buf[256]; // Buffer for client data

    // If not the listener, we're just a regular client
    int nbytes = recv(fd, buf, sizeof buf, 0);

    int sender_fd = fd;

    if (nbytes <= 0)
    {
        // Got error or connection closed by client
        if (nbytes == 0)
        {
            // Connection closed
            printf("pollserver: socket %d hung up\n", sender_fd);
        }
        else
        {
            perror("recv");
        }

        close(fd); // Bye!
        removeHandller(rec, index);
    }
    else
    {
        // We got some good data from a client
        buf[nbytes - 1] = '\0';
        printf("Message: %s\n", buf);

        for (int j = 0; j < rec->fd_count; j++)
        {
            // Send to everyone!
            int dest_fd = rec->fds[j].fd;

            // Except the listener and ourselves
            if (dest_fd != rec->listener && dest_fd != sender_fd)
            {
                if (send(dest_fd, buf, nbytes, 0) == -1)
                {
                    perror("send");
                }
            }
        }
    }
}

void *runnable(void *args)
{
    Reactor *rec = (Reactor *)args;

    while (1)
    {
        int poll_count = poll(rec->fds, rec->fd_count, -1);

        if (poll_count == -1)
        {
            perror("poll");
            exit(1);
        }

        for (int i = 0; i < rec->fd_count; i++)
        {
            if (rec->fds[i].revents & POLLIN)
            {
                rec->funcs[i](rec->fds[i].fd, rec, i);
            }
        }
    }
    return NULL;
}

Reactor *newReactor()
{
    Reactor *rec = (Reactor *)malloc(sizeof(Reactor));
    rec->fd_count = 0;
    rec->fd_size = 5;
    rec->listener = -1;
    rec->fds = (struct pollfd *)calloc(sizeof *rec->fds * rec->fd_size, 0);
    for (size_t i = 0; i < SIZE; i++)
    {
        rec->funcs[i] = 0;
    }
    return rec;
}

void installHandller(Reactor *rec, int fd, void (*fun)(int, Reactor *, int))
{
    // If we don't have room, add more space in the pfds array
    if (rec->fd_count == rec->fd_size)
    {
        rec->fd_size *= 2; // Double it
        rec->fds = (struct pollfd *)realloc(rec->fds, sizeof(*rec->fds) * (rec->fd_size));
    }

    (rec->fds)[rec->fd_count].fd = fd;
    (rec->fds)[rec->fd_count].events = POLLIN; // Check ready-to-read
    rec->funcs[rec->fd_count] = fun;

    (rec->fd_count)++;

    if (rec->listener == -1)
    {
        rec->listener = fd;
        pthread_create(&rec->thread_id, NULL, runnable, rec);
    }
}

void removeHandller(Reactor *rec, int i)
{
    // Copy the one from the end over this one
    rec->fds[i] = rec->fds[rec->fd_count - 1];
    (rec->fd_count)--;
}
