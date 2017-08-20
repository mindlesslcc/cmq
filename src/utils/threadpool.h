#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include <atomic>
#include <thread>
#include <mutex>
#include <array>
#include <queue>
#include <functional>
#include <condition_variable>

namespace cmq {

namespace utils {

class ThreadPool {

public:
    ThreadPool(int size = 10);
    ~ThreadPool();
    void AddTask(std::function<void(void)>);

private:
    std::function<void(void)> NextTask();
    void Task();

    std::atomic_int _size;
    std::atomic_bool _running;
    std::mutex _qmu;
    std::condition_variable _waitTask;
    std::vector<std::thread> _workers;
    std::queue<std::function<void(void)>> _tasks;
};

ThreadPool::ThreadPool(int size) : _size(size), _running(true), _workers(size) {
    for (int i=0;i<_size;++i) {
        _workers[i] = std::thread([this] {this->Task();});
    }
}

ThreadPool::~ThreadPool() {
    _running = false;
    for(auto &thread : _workers) {
        thread.join();
    }
}

void ThreadPool::AddTask(std::function<void(void)> func) {
    std::unique_lock<std::mutex> lock(_qmu);
    _tasks.emplace(func);
    _waitTask.notify_one();
}

void ThreadPool::Task() {
    do {
        std::function<void(void)> func = NextTask();
        func();
        
    } while(_running);
}

std::function<void(void)> ThreadPool::NextTask() {
    std::function<void(void)> func;
    {
        std::unique_lock<std::mutex> lock(_qmu);
        _waitTask.wait(lock, [this]() ->bool {return !_tasks.empty();});
        func = _tasks.front();
        _tasks.pop();
    }
    return func;
}
} // end of namespace utils
} // end of namespace cmq

#endif
