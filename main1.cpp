#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "main1.hpp"

Queue *q1, *q2, *q3;
// Declaration of thread condition variable
static pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
static pthread_mutex_t lock1= PTHREAD_MUTEX_INITIALIZER;

void printQ(Queue *q)
{
    QNode *p = q->root;
    printf("\n\n");
    while (p)
    {
        printf("->%s\n", p->data);
        p = p->next;
    }
}

void destroyQ(Queue *queue)
{
    pthread_mutex_lock(&lock1);

    if (!queue || !queue->root)
    {
        free(queue);
        return;
    }

    QNode *p = queue->root;
    while (p)
    {
        QNode *temp = p->next;
        free(p);
        p = temp;
    }
    queue->size = 0;
    queue->root = NULL;
    free(queue);
    printf("Queue was destroied\n");
    pthread_mutex_unlock(&lock1);
}

void createQ(Queue **queue)
{
    if (*queue)
    {
        destroyQ(*queue);
    }
    *queue = (Queue *)malloc(sizeof(Queue));
    (*queue)->root = 0;
    (*queue)->size = 0;
    (*queue)->tail = 0;
}

void enQ(Queue *queue, const void *data)
{
    if (!queue || !data)
    {
        printf("ERROR: something went wrong %p\n",queue);
        return;
    }
    pthread_mutex_lock(&lock1);
    QNode *p = (QNode *)malloc(sizeof(QNode));

    p->data = data;
    p->next = NULL;

    if (!queue->root)
    {
        queue->root = queue->tail = p;
        queue->size++;
        pthread_cond_broadcast(&cond1);
        pthread_mutex_unlock(&lock1);
        return;
    }
    queue->tail->next = p;
    queue->tail = p;
    queue->size++;
    pthread_cond_broadcast(&cond1);
    pthread_mutex_unlock(&lock1);
}

void *deQ(Queue *queue)
{
    if (!queue)
    {
        printf("ERROR: queue is NULL\n");
        return NULL;
    }
    pthread_mutex_lock(&lock1);
    while (queue->size == 0)
    {
        // waiting on cond, No elemnts to be dequeued
        // printf("waiting on cond\n");
        pthread_cond_wait(&cond1, &lock1);
    }
    void *temp = (void *)queue->root->data;
    void *p = queue->root;
    queue->root = queue->root->next;
    free(p);
    queue->size--;
    pthread_mutex_unlock(&lock1);
    return temp;
}

void *peek(Queue *queue)
{
    if (queue->size == 0)
    {
        printf("ERROR: queue is empty\n");
        return NULL;
    }

    printf("OUTPUT: %s\n", queue->root->data);
    return (char *)queue->root->data;
}

//--------------------------------------------------------------------------------------


void afterFunc1(QData *p)
{
    enQ(q2, p);
};

void afterFunc2(QData *p)
{
    enQ(q3, p);
};

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