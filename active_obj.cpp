#include "active_obj.hpp"
#include "queue.hpp"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief the encoding function
 *
 * @param d
 */
void encode(QData *d)
{
    printf("encode: %s\n", (char *)d->data);

    char *p = (char *)d->data;
    while (*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = ((*p - 'A' + 1) % 26) + 'A';
        }
        else if (*p >= 'a' && *p <= 'z')
        {
            *p = (((*p - 'a') + 1) % 26) + 'a';
        }
        p++;
    }
    printf("after encode: %s\n", (char *)d->data);
    fflush(stdout);
}

/**
 * @brief sawping Cap letter with small and vice versa
 *
 * @param d
 */
void swapBigAndSmall(QData *d)
{
    printf("swaping big and small: %s\n", (char *)d->data);
    char *p = (char *)d->data;
    while (*p)
    {
        if (*p >= 'A' && *p <= 'Z')
        {
            *p = 'a' + *p - 'A';
        }
        else if (*p >= 'a' && *p <= 'z')
        {
            *p = 'A' + *p - 'a';
        }
        p++;
    }
    printf("after swaping: %s\n", (char *)d->data);
    fflush(stdout);
}

/**
 * @brief sending a response to the client
 *
 * @param p
 */
void response(QData *p)
{
    printf("Sending response\n");
    int stdoutfd = dup(1);
    dup2(p->fd, 1);
    printf("%s\n", p->data);
    dup2(stdoutfd, 1);
    printf("---------------------------\n");
    free(p);
}

void *ActiveObject::runnable(void *args)
{
    ActiveObject *act = (ActiveObject *)args;
    printf("Runnable %d started\n", act->id);
    while (1)
    {
        QData *p = (QData *)deQ(act->q);
        act->f1(p);
        if (act->f2)
        {
            act->f2(p);
        }
    }
    return NULL;
};

pthread_t ActiveObject::newAO(Queue *q, void fun1(QData *), void afterFunc(QData *))
{
    pthread_t tid;
    this->f1 = fun1;
    this->f2 = afterFunc;
    this->q = q;
    pthread_create(&tid, NULL, runnable, this);
    return tid;
}

void ActiveObject::destroyAO(pthread_t tid, Queue *q)
{
    pthread_cancel(tid);
    destroyQ(q);
}