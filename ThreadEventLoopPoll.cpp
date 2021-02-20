#include"ThreadEventLoopPoll.h"
ThreadEventLoopPoll::ThreadEventLoopPoll(std::shared_ptr<EventLoop> baseloop,int threadnum):
    baseloop_(baseloop),
    threadnum_(threadnum),
    next_(0)
{

}
void ThreadEventLoopPoll::start(){
    for(int i=0;i<threadnum_;i++){
        std::shared_ptr<ThreadEventLoop> eventloop(new ThreadEventLoop());
        loops_.push_back(eventloop);
    }
}
 std::shared_ptr<EventLoop> ThreadEventLoopPoll::getNextEventloop(){
    std::shared_ptr<ThreadEventLoop> loop;
    if(!loops_.empty()){
        loop=loops_[next_];
        next_=(next_+1)%threadnum_;
    }
    return loop->getEventloop();
}