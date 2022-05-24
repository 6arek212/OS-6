#pragma once 
#include "queue.hpp"
#include <pthread.h>



void encode(QData *d);
void swapBigAndSmall(QData *d);
void response(QData *p);


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