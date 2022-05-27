#pragma once
#include <pthread.h>

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

extern Queue *q1;
extern Queue *q2;
extern Queue *q3;

void enQ(Queue *queue, const void *data);
void *deQ(Queue *queue);
void *peek(Queue *queue);
void destroyQ(Queue *queue);
void createQ(Queue **queue);

//----------------------------------------------------------

void encode(QData *d);
void swapBigAndSmall(QData *d);
void response(QData *p);
void afterFunc1(QData *p);
void afterFunc2(QData *p);

class ActiveObject
{

private:
    Queue *q;
    void (*f1)(QData *);
    void (*f2)(QData *);
    int id;

    static void *runnable(void *args);

public:
    ActiveObject(int id)
    {
        this->id = id;
    }
    pthread_t newAO(Queue *q, void fun1(QData *), void afterFunc(QData *));
    void destroyAO(pthread_t tid, Queue *q);
};