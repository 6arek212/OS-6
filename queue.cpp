#include "queue.hpp"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

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

void destroyQ(Queue *queue)
{
    pthread_mutex_lock(&lock);

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
    pthread_mutex_unlock(&lock);
}

void enQ(Queue *queue, const void *data)
{
    if (!queue || !data)
    {
        printf("ERROR: something went wrong\n");
        return;
    }
    pthread_mutex_lock(&lock);
    QNode *p = (QNode *)malloc(sizeof(QNode));

    p->data = data;
    p->next = NULL;

    if (!queue->root)
    {
        queue->root = queue->tail = p;
        queue->size++;
        pthread_cond_broadcast(&cond1);
        pthread_mutex_unlock(&lock);
        return;
    }
    queue->tail->next = p;
    queue->tail = p;
    queue->size++;
    pthread_cond_broadcast(&cond1);
    pthread_mutex_unlock(&lock);
}

void *deQ(Queue *queue)
{
    if (!queue)
    {
        printf("ERROR: queue is NULL\n");
        return NULL;
    }
    pthread_mutex_lock(&lock);
    while (queue->size == 0)
    {
        // waiting on cond, No elemnts to be dequeued
        // printf("waiting on cond\n");
        pthread_cond_wait(&cond1, &lock);
    }
    void *temp = (void *)queue->root->data;
    void *p = queue->root;
    queue->root = queue->root->next;
    free(p);
    queue->size--;
    pthread_mutex_unlock(&lock);
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
