#include "mu_lock.h"
#include <iostream>
#include <mutex>

int main()
{
    clock_t start = 0, end = 0;
    Mutex m;
/*    start = clock();
    for (int i=0;i<100000000;++i) {
        m.Lock();
        m.UnLock();
    }
    end = clock();
    std::cout<<(double)(end - start) / CLOCKS_PER_SEC<<std::endl;
    // std::mutex
    std::mutex mu;
    start = clock();
    for (int i=0;i<100000000;++i) {
        mu.lock();
        mu.unlock();
    }
    end = clock();
    std::cout<<(double)(end - start) / CLOCKS_PER_SEC<<std::endl;*/
    // std::mutex
    start = clock();
    for (int i=0;i<100000000;++i) {
        MutexLock lock(&m);
    }
    end = clock();
    std::cout<<(double)(end - start) / CLOCKS_PER_SEC<<std::endl;
    return 0;
}
