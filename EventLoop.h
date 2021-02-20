#pragma once
#include<functional>
#include<vector>

#include"EPoller.h"
#include"Channel.h"
#include"Util.h"
#include<iostream>
#include"Mutex.h"
typedef std::function<void*(void*)> Fun;

struct attr{
    int fd;
    std::shared_ptr<EventLoop> loop;
};
struct Functor{
    Fun fun;
    attr a;
};

class EventLoop{
public:

    EventLoop();
    typedef std::function<void()> callback;
    void loop();
    EPoller* getEPoll(){return poller_;}
    void wakeup();
    void setfd(int fd){fd_=fd;}
    void addfd();
    std::mutex& getMutex(){return mutex_;}
    void appendingFuntor(Functor& f){funs_.push_back(std::move(f));}
private:
    EPoller* poller_;
    int wakeupfd_;
    bool quit_;
    int fd_;
    std::mutex mutex_;
    std::vector<Functor> funs_;
};