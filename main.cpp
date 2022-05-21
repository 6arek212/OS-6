#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.hpp"

Queue *q;



void *f1(void *args)
{

    printf("%s\n", deQ(q));
    return NULL;
}

void *f2(void *args)
{
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;

    createQ(&q);
    enQ(q, "Tarik");
    enQ(q, "aaa");

    printf("%s\n", deQ(q));
    printf("%s\n", deQ(q));

    destroyQ(q);

    // pthread_create(&tid1, NULL, f2, NULL);

    // sleep(1);

    // pthread_create(&tid2, NULL, f2, NULL);
    // pthread_join(tid2, NULL);
    // pthread_join(tid1, NULL);

    return 0;
}
