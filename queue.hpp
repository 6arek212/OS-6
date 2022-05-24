#pragma once

typedef struct QData
{
    void *data;
    int fd;
} QData;

typedef struct QNode
{
    const void *data;
    struct QNode *next;
} QNode;

typedef struct Queue
{
    int size;
    QNode *root;
    QNode *tail;
} Queue;

void enQ(Queue *queue, const void *data);
void *deQ(Queue *queue);
void *peek(Queue *queue);
void destroyQ(Queue *queue);
void createQ(Queue **queue);
