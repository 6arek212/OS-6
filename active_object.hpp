#include "queue.hpp"
#include <pthread.h>

class ActiveObject
{

private:
    void (*fun)(void *);
    void (*afterFunc)(void *);

public:
    void *runnable(void *args)
    {
        while (1)
        {
            void *p = deQ(q);
            fun(p);
            afterFunc(p);
        }
        return NULL;
    }

    pthread_t newAO(Queue *queue, void fun(void *), void afterFunc(void *))
    {
        pthread_t tid;
        this->fun = fun;
        this->afterFunc = afterFunc;
        pthread_create(&tid, NULL, runnable);
        return tid;
    }

    void destroyAO(pthread_t threadId, Queue *queue)
    {
        pthread_cancel(threadId);
        destroyQ(queue);
    }
}
