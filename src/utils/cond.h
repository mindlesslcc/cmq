#ifndef _COND_H
#define _COND_H

#include <time.h>
#include <pthread.h>

#include "mu.h"

class Cond {
public:
    Cond(){
        pthread_cond_init(&_cond, NULL);
    }
    Cond(Cond &) = delete;
    void operator=(Cond &) = delete;
    ~Cond(){
        pthread_cond_destroy(&_cond);
    }
    void Wait(MutexBase *m) {
        pthread_cond_wait(&_cond, &m->_mu);
    }
    // us
    int WaitTimeOut(int timeout) {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        int64_t nsec = ((int64_t)timeout) * 1000 + ts.tv_nsec;
        ts.tv_sec += nsec / 1000000000;
        ts.tv_nsec = nsec % 1000000000;

        return pthread_cond_timedwait(&cond_, &mu_->mu_, &ts);
    }
    void Signal() {
        pthread_cond_signal(&_cond);
    }
    void SignalAll() {
        pthread_cond_brodcast(&_cond);
    }
private:
    pthread_cond_t _cond;
};

#endif
