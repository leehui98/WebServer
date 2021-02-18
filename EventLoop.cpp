#include"EventLoop.h"
EventLoop::EventLoop():
   poller_(new EPoller),
   wakeupfd_(geteventfd())
{

}
void EventLoop::loop()
{

    std::vector<SP_Channel> active;
    while(true){
        active=std::move(poller_->poll());
        for(auto i:active) i->handleEvent();
    }
    
}
void EventLoop::wakeup(){
    uint64_t one=1;
    ssize_t n=writen(wakeupfd_,reinterpret_cast<char*>(&one),sizeof(one));
    if(n!=sizeof one){
        ;
    }
}