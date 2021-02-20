#pragma once
#include"EventLoop.h"
#include"Thread.h"
class ThreadEventLoop{
public:
    ThreadEventLoop();
    std::shared_ptr<EventLoop> getEventloop(){return eventloop_;}
    void runFun();
private:
    std::shared_ptr<EventLoop> eventloop_;
    Thread thread_;
};