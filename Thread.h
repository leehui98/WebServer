#pragma once 
#include<functional>
#include<pthread.h>
class Thread{
public:
    typedef std::function<void()> Fun;
    Thread(Fun fun);
    void start();
    void join();
    static void* threadfun(void* attr);
private:
    Fun fun_;
    pthread_t pthreadID_;
};