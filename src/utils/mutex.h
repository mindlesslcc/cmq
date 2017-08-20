#ifndef _MUTEX_H
#define _MUTEX_H

#include <iostream>
#include <mutex>
#include <pthread.h> 

class MutexBase {
public:
    virtual void Lock() = 0;
    virtual void UnLock() = 0;
    virtual int TryLock() = 0;
};

class Mutex : public MutexBase {
public:
    Mutex() {
        pthread_mutex_init(&_mu, NULL);
    }
    ~Mutex() {
        pthread_mutex_destroy(&_mu);
    }
    void Lock() {
        pthread_mutex_lock(&_mu);
    }
    int TryLock() {
        return pthread_mutex_trylock(&_mu);
    }
    void UnLock() {
        pthread_mutex_unlock(&_mu);
    }
private:
    pthread_mutex_t _mu;
};

#endif
