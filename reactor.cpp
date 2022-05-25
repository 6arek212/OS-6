#include <vector>

typedef struct ReactorData
{
    int fd;
    void *(*fun)(void *);
} ReactorData;

typedef struct Reactor
{
    std::vector<ReactorData> handlers;

} Reactor;

void *newReactor(Reactor *rec, int fd)
{
    return new Reactor();
}

void installlHandler(Reactor *rec, int fd, void *fun(void *))
{
    ReactorData d;
    d.fd = fd;
    d.fun = fun;
    rec->handlers.push_back(d);
}

void removeHandler(Reactor *rec, int fd)
{
    int i = 0;
    for (ReactorData d : rec->handlers)
    {
        if (d.fd == fd)
        {
            rec->handlers.erase(rec->handlers.begin() + i);
            return;
        }
        i++;
    }
}