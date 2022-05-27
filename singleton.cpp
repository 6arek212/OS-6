#include <stdlib.h>

template <class T>
class Singleton
{
private:
    static T *obj;
    Singleton() {}
    ~Singleton() {}

public:
    static T * instance()
    {
        if (Singleton::obj == NULL)
        {
            Singleton::obj = new T();
            *Singleton::obj = 0;
        }
        return Singleton::obj;
    }

    static void destroy()
    {
        if (Singleton::obj == NULL)
        {
            return;
        }
        delete Singleton::obj;
    }
};

template <class T>
T *Singleton<T>::obj = NULL;