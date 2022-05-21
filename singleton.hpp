#include "guard.hpp"
#include <pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

template <class T>
class Singleton
{

private:
    static T *obj;

public:
    static T *instance()
    {
        Guard g(lock);
        if (!obj)
        {
            obj = new T();
        }
        return obj;
    }

    void destroy()
    {
        Guard g(lock);
        if (!obj)
        {
            return;
        }
        delete obj;
        obj = 0;
    }
}