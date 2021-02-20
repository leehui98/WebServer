#include"ThreadEventLoop.h"
ThreadEventLoop::ThreadEventLoop():
    eventloop_(new EventLoop()),
    thread_(std::bind(&ThreadEventLoop::runFun,this))
{
    thread_.start();
}
void ThreadEventLoop::runFun(){
    eventloop_->loop();
}