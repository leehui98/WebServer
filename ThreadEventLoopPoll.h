#pragma once 
#include"EventLoop.h"
#include"ThreadEventLoop.h"
class ThreadEventLoopPoll{
public:
    ThreadEventLoopPoll(std::shared_ptr<EventLoop> baseloop,int threadnum);
    std::shared_ptr<EventLoop> getNextEventloop();
    void start(); 
private:
    int next_;
    int threadnum_;
    std::shared_ptr<EventLoop>  baseloop_;
    std::vector<std::shared_ptr<ThreadEventLoop>> loops_;
    int quit_;
};