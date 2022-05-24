#include <stdio.h>
#include "singleton.cpp"
#include <stdio.h>
#include <sys/mman.h>
#include <assert.h>

int main(int argc, char const *argv[])
{

    printf("%d \n", Singleton<int>::instance());

    double &y = Singleton<double>::instance();
    y = 1.3;

    int &x = Singleton<int>::instance();
    x++;

    printf("%d  %f\n", Singleton<int>::instance(), Singleton<double>::instance());

    Singleton<double>::destroy();
    Singleton<int>::destroy();

    x = 5;
    y= 5555.55;


    
    // int N = 5;


    // Singleton<void *>::instance() = mmap(NULL, N * sizeof(int),
    //                 PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    // assert(Singleton<void*>::instance() == Singleton<void*>::instance());

    return 0;
}
