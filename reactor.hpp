#include <poll.h>
#include <netdb.h>
#include <pthread.h>
#define SIZE 1024

typedef struct Reactor
{
    struct pollfd *fds;
    void (*funcs[SIZE])(int, Reactor *, int index);
    int fd_count;
    int fd_size;
    int listener;
    pthread_t thread_id;
} Reactor;

Reactor *newReactor();
void installHandller(Reactor *rec, int fd, void (*fun)(int, Reactor *, int));
void removeHandller(Reactor *rec, int i);
void accept1(int fd, Reactor *rec, int index);
void recv1(int fd, Reactor *rec, int index);