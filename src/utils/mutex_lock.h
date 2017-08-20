#ifndef _MUTEX_LOCK_H
#define _MUTEX_LOCK_H

#include "mu.h"

class MutexLock {
public:
    MutexLock(MutexBase *mu) {
        _mu = mu;
        _mu->Lock();
    }
    MutexLock() = delete;
    MutexLock(MutexLock &) = delete;
    void operator=(MutexLock &) = delete;
    ~MutexLock() {
        if (_mu) {
            _mu->UnLock();
        }
    }
private:
    MutexBase *_mu;
};

#endif
