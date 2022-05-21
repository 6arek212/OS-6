#include "guard.hpp"

Guard::Guard(pthread_mutex_t *lock)
{
    this->lock = lock;
    pthread_mutex_lock(this->lock);
}

Guard::~Guard()
{
    pthread_mutex_unlock(this->lock);
};