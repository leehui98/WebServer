#pragma once
#include<mutex>
#include"nocopyable.h"
class MutexGuard:nocopyable{
public:
    MutexGuard(std::mutex& mutex):
    mutex_(mutex)
    {
        mutex_.lock();
    }
    ~MutexGuard(){
        mutex_.unlock();
    }
private:
    std::mutex& mutex_;
};