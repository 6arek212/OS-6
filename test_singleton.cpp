#include "singleton.cpp"
#include <assert.h>
#include <stdio.h>
// Driver code
int main()
{

    int *p = Singleton<int>::instance();
    *p = 5;

    assert((Singleton<int>::instance() == Singleton<int>::instance()));

    assert(*Singleton<int>::instance() == *Singleton<int>::instance());

    printf("singleton test success\n");
    return 0;
}