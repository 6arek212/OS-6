#include "singleton.cpp"
#include <assert.h>
#include <stdio.h>
// Driver code
int main()
{

    int *p = Singleton<int>::instance();
    *p = 5;

    printf("Singleton value %d\n", *p);

    assert((Singleton<int>::instance() == Singleton<int>::instance()));

    assert(*Singleton<int>::instance() == *Singleton<int>::instance());

    Singleton<int>::destroy();
    
    printf("singleton test success\n");
    return 0;
}