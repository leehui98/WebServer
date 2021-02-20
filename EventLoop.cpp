#include"EventLoop.h"
EventLoop::EventLoop():
   poller_(new EPoller),
   wakeupfd_(geteventfd()),
   quit_(false)
{
    std::shared_ptr<Channel> channel(new Channel(static_cast<std::shared_ptr<EventLoop>>(this),wakeupfd_));
    channel->setCallRead(std::bind(&EventLoop::addfd,this));
    this->getEPoll()->epoll_add(channel);
}
void EventLoop::loop()
{

    std::vector<SP_Channel> active;
    while(!quit_){
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

void EventLoop::addfd(){//添加用户
    //std::cout<<"wake and add fd"<<std::endl;
    std::vector<Functor> funs;
     {
            MutexGuard lock(getMutex());
            funs.swap(funs_);
    }
    for(int i=0;i<funs.size();i++)
     funs[i].fun((void*)(&funs[i].a));
}