

#include <pthread.h>




/**
 * @brief 
 *       Q.4
 * 
 * we can use the guard class to make strtok a thread sfae,
 * simply by wrapping the strtok with another function that uses the gaurd class at the first line of 
 * that function
 * 
 * 
 */
class Guard
{
private:
    pthread_mutex_t *lock;

public:
    Guard(pthread_mutex_t *lock);
    ~Guard();
};