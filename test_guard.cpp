#include "guard.hpp"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int cnt = 0;

void *func(void *args)
{
    Guard g(&lock);
    for (size_t i = 0; i < 200; i++)
    {
        cnt++;
        printf("%d\n", cnt);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2, tid3;

    pthread_create(&tid1, NULL, func, NULL);
    pthread_create(&tid2, NULL, func, NULL);
    pthread_create(&tid3, NULL, func, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    printf("test guard successful \n");
    return 0;
}
